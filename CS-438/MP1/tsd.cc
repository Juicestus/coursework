// -*- coding: utf-8 -*-
// Copyright (C) <2026> <Texas A&M University>
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//
// For AGPL-specific network service requirements, see the full license.
//


#include <ctime>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/duration.pb.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <mutex>

#include <google/protobuf/util/time_util.h>
#include <grpc++/grpc++.h>
#include <glog/logging.h>
#define log(severity, msg) LOG(severity) << msg; google::FlushLogFiles(google::severity); 

#include "sns.grpc.pb.h"
#include "ini.h"

using google::protobuf::Timestamp;
using google::protobuf::Duration;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using csce_dsc::Message;
using csce_dsc::ListReply;
using csce_dsc::Request;
using csce_dsc::Reply;
using csce_dsc::SNSService;

struct Client {
  std::string username;
  bool connected = true;
  int following_file_size = 0;
  std::vector<Client*> client_followers;
  std::vector<Client*> client_following;
  ServerReaderWriter<Message, Message>* stream = 0;
  time_t last_hb;
  bool in_timeline = false;
  bool operator==(const Client& c1) const{
    return (username == c1.username);
  }

  Client(const std::string& username) : username(username), last_hb(0) {}

  Client(const std::string& username, bool connected) 
  : username(username), connected(connected), last_hb(0) {}

  void loadFollowing();
  void saveFollowing();
};

//Vector that stores every client that has been created
std::vector<Client*> client_db;
std::mutex client_db_mut;

Client* getClient(const std::string& username, bool create = true)
{
  std::lock_guard<std::mutex> lock(client_db_mut);  // scoped_lock

  for (Client* c : client_db) {
    if (c->username == username) {
      return c;
    }
  }

  if (create) {
    Client* c = new Client(username, false);
    client_db.push_back(c);
    return c;
  }
  return nullptr;
}


void Client::loadFollowing()
{
  std::ifstream file("__" + username + "_following.txt");
  if (!file.is_open()) {
    // log(ERROR, "Failed to open following file for " + username);
    return;
  }

  std::string _username;
  while (std::getline(file, _username)) {
    if (!_username.empty()) {
      Client* followed = getClient(_username);

      bool already = false;
      for (Client* c : client_following) {
        if (c->username == _username) {
          already = true;
          break;
        }
      }
      if (!already) {
        client_following.push_back(followed);
        followed->client_followers.push_back(this);        
      }
    }
  }

  file.close();
}

void Client::saveFollowing() 
{
  std::ofstream file("__" + username + "_following.txt", std::ios::trunc);  

  if (!file.is_open()) {
    log(ERROR, "Failed to open following file for " + username);
    return;
  }
  
  for (Client* followed : client_following) {
    file << followed->username << "\n";
  }
  file.close();
}

class SNSServiceImpl final : public SNSService::Service {
  
  Status List(ServerContext* context, const Request* request, ListReply* list_reply) override {
    log(INFO, "List request from " + request->username());
    // c = client_db[request->username];
    Client* user = getClient(request->username());
    std::lock_guard<std::mutex> lock(client_db_mut);

    // add users in client_db to list_reply;
    for (Client* c : client_db) {
      list_reply->add_all_users(c->username);
    }

    // add (followers of c) to list_reply;
    for (Client* f : user->client_followers) {
      list_reply->add_followers(f->username);
    }

    return Status::OK;
  }

  Status Follow(ServerContext* context, const Request* request, Reply* reply) override {

    // u1, u2 = request.username, request.args[0]
    std::string u1 = request->username();
    std::string u2 = request->arguments(0);

    log(INFO, "Follow request from " + u1 + ", following " + u2);

    if (u1 == u2) {
      reply->set_msg("you cannot follow yourself");  
      log(WARNING, u1 + " tried to follow self");
      return Status::OK;
    }

    // c1, c2 = getClient(u1), getClient(u2)
    Client* c1 = getClient(u1);
    Client* c2 = getClient(u2, false);

    if (!c2) {
      reply->set_msg("user does not exist");
      log(WARNING, "User " + u2 + " does not exist");
      return Status::OK;
    }

    for (Client* c : c1->client_following) {  
      if (c->username == u2) {
        reply->set_msg("you have already joined");
        log(INFO, u1 + " already follows " + u2);
        return Status::OK;
      }
    }

    c1->client_following.push_back(c2);  
    c2->client_followers.push_back(c1);

    c1->saveFollowing(); 
    reply->set_msg("Follow Successful");
    log(INFO, u1 + " follows " + u2);

    return Status::OK; 
  }

  Status UnFollow(ServerContext* context, const Request* request, Reply* reply) override {

   
    // u1, u2 = request.username, request.args[0]
    std::string u1 = request->username();
    std::string u2 = request->arguments(0);

    log(INFO, "UnFollow request from " + u1 + ", unfollowing " + u2);

    // c1, c2 = getClient(u1), getClient(u2)
    Client* c1 = getClient(u1);
    Client* c2 = getClient(u2, false);

    if (!c2) {
      reply->set_msg("user does not exist");
      return Status::OK;
    }

    // c1.client_following.erase(u2);
    bool found = false;
    for (auto it = c1->client_following.begin(); it != c1->client_following.end(); ++it) {
      if ((*it)->username == u2) {
        c1->client_following.erase(it);
        found = true;
        break;
      }
    }

    if (!found) {
      reply->set_msg("You are not a follower");
      log(WARNING, u1 + " is not following " + u2);
      return Status::OK;
    }

    // c2.client_followers.erase(u1);
    for (auto it = c2->client_followers.begin(); it != c2->client_followers.end(); ++it) {
      if ((*it)->username == u1) {
        c2->client_followers.erase(it);
        break;
      }
    }

    c1->saveFollowing();
    reply->set_msg("UnFollow Successful");
    log(INFO, u1 + " unfollowed " + u2);

    return Status::OK;
  }

  // RPC Connect
  Status Connect(ServerContext* context, const Request* request, Reply* reply) override {

    // ic = getClient(request.username)
    std::string u = request->username();
    log(INFO, "Connection request from " + u);

    Client* c = getClient(u);
    // if (c.connected){
    if (c->connected) {
    //    connection failed
      reply->set_msg("you are already connected");
      log(WARNING, u + " already connected");
      return Status::OK;
    } else {
    //    connection succeeded
      c->loadFollowing();
      c->connected = true;
      c->last_hb = time(0);

      reply->set_msg("Connection Successful");
      log(INFO, u + " connected");
    }
    
    return Status::OK;
  }

Status Timeline(ServerContext* context,  ServerReaderWriter<Message, Message>* stream) override {

    Message m;
    
    // while(stream.read(&m)){
    int i;
    for ( i = 0; stream->Read(&m); i++) {

    //    string u = m.username
      std::string u = m.username();
    //    Client c = getClient(u)
      Client* c = getClient(u);

      if (i == 0) {
        log(INFO, u + " entered timeline");
        c->stream = stream;
        c->in_timeline = true;

        //    }else{
        //       lat20 = read 20 latest massages from file u_following.txt;
        //     stre
        std::ifstream tl_in("__" + u + "_timeline.txt");

        if (tl_in.is_open()) {
          std::vector<std::string> lines;
          std::string line;
          while (std::getline(tl_in, line)) {
            lines.push_back(line);
          }
          tl_in.close();

          int num_posts = lines.size() / 4;
          int start = (num_posts > 20) ? (num_posts - 20) : 0;
          int start_line = start * 4;

          for (size_t i = start_line; i < lines.size(); i += 4) {
            if (i + 2 < lines.size()) {
              Message msg;

              std::string t_line = lines[i];
              if (t_line.length() > 2) {
                std::string t_str = t_line.substr(2);
                struct tm tm = {};
                strptime(t_str.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
                time_t t = mktime(&tm);
                Timestamp *ts = new Timestamp();
                ts->set_seconds(t);
                ts->set_nanos(0);
                msg.set_allocated_timestamp(ts);
              }

              std::string u_line = lines[i + 1];
              if (u_line.length() > 2) {
                msg.set_username(u_line.substr(2));
              }

              std::string m_line = lines[i + 2];
              if (m_line.length() > 2) {
                msg.set_msg(m_line.substr(2));
              }

              stream->Write(msg);
            }
          }
        }
      }
    //    if(!first_timeline_stream()){
    //       append ffo to file u.txt
    // }

      if (m.msg().empty() || m.msg() == "\n") {
        continue;  
      }
      //    ffo = format_file_output(timestamp, request.username, m)
      time_t now = m.timestamp().seconds();
      struct tm *ti = localtime(&now);
      char buf[80];
      strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ti);

      std::string ffo = "T " + std::string(buf) + "\n" + "U " + u + "\n" + "W " + m.msg() + "\n";

      // Append ffo to file u.txt
      std::ofstream u_out("__" + u + ".txt", std::ios::app);
      if (u_out.is_open()) {
        u_out << ffo;
        u_out.close();
      }

      // For each follower: write to stream and append to f_timeline.txt
    //    for f in c.followers:
    //       f->stream->write(ffo)
    //       append ffo to the file f_following.txt    
      for (Client *f : c->client_followers) {
        if (f->stream && f->in_timeline) {
          f->stream->Write(m);
        }

        std::ofstream f_out("__" + f->username + "_timeline.txt", std::ios::app);
        if (f_out.is_open()) {
          f_out << ffo;
          f_out.close();
        }
      }
    }

    if (i > 0) { // Only if we actually entered timeline
      Client *c = getClient(m.username());
      c->stream = nullptr;
      c->in_timeline = false;
      c->connected = false;
      log(INFO, m.username() + " left timeline");
    }

   
    
    return Status::OK;
  }


  // RPC Heartbeat
  Status Heartbeat(ServerContext* context, const google::protobuf::Empty* request, 
      google::protobuf::Empty* reply) override {

    auto md = context->client_metadata();
    auto it = md.find("username");
    if (it != md.end())
    {
      std::string username(it->second.data(), it->second.size());
      Client* c = getClient(username);
      c->last_hb = time(0);
      log(INFO, "Rx heartbeat from " + username);
    }

    return Status::OK;
  }
};
 
void RunServer(std::string port_no) {
  std::string server_address = "0.0.0.0:"+port_no;
  SNSServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  log(INFO, "Server listening on: "+server_address);

  // heartbeat checker thread 
  std::thread heartbeat_thread([&]() {
     while (true) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

      time_t now = time(0);
      std::lock_guard<std::mutex> lock(client_db_mut);

      for (Client* c : client_db) {
        if (c->connected) {
          if (difftime(now, c->last_hb) >= 1.0) {   // 1s timeout
            c->connected = false;
            c->in_timeline = false;
            c->stream = nullptr;
            log(INFO, c->username + " timed out");
          }
        }
      }
    }
  });
  heartbeat_thread.detach();

  server->Wait();
}

int main(int argc, char** argv) {

   if(argc != 2) {
	   std::cerr << "Invalid Command Line Arguments: Usage .\\tsd <config.ini>\n";
           exit(0);
   }

  mINI::INIFile file(argv[1]);
  mINI::INIStructure ini;

  // read the config file
  file.read(ini);

  // read configuration values
  std::string&  port = ini["Server"]["PORT"];
  std::string&  logLevel = ini["Glog"]["MIN_LOG_LEVEL"];
  std::string&  logDir = ini["Glog"]["LOG_DIR"];

  // Disable glog buffering for immediate output
  FLAGS_logbuflevel = -1;
  FLAGS_timestamp_in_logfile_name = 0;
  
  FLAGS_minloglevel = std::stoi(logLevel); 
  FLAGS_log_dir = logDir;

  std::string log_file_name = std::string("server-") + port;
  google::InitGoogleLogging(log_file_name.c_str());
  log(INFO, "Logging Initialized. Server starting ...");

  RunServer(port);

  return 0;
}


