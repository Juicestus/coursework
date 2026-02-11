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


#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>
#include <unistd.h>
#include <csignal>
#include <grpc++/grpc++.h>
#include <google/protobuf/empty.pb.h>
#include "client.h"

#include "sns.grpc.pb.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using csce_dsc::Message;
using csce_dsc::ListReply;
using csce_dsc::Request;
using csce_dsc::Reply;
using csce_dsc::SNSService;

void sig_ignore(int sig) {
  std::cout << "Signal caught " + sig;
}

Message MakeMessage(const std::string& username, const std::string& msg) {
    Message m;
    m.set_username(username);
    m.set_msg(msg);
    google::protobuf::Timestamp* timestamp = new google::protobuf::Timestamp();
    timestamp->set_seconds(time(NULL));
    timestamp->set_nanos(0);
    m.set_allocated_timestamp(timestamp);
    return m;
}


class Client : public IClient
{
public:
  Client(const std::string& hname,
	 const std::string& uname,
	 const std::string& p)
    :hostname(hname), username(uname), port(p) {}

  
protected:
  virtual int    connectTo();
  virtual IReply processCommand(std::string& input);
  virtual void   processTimeline();

private:
  std::string hostname;
  std::string username;
  std::string port;
  
  std::unique_ptr<SNSService::Stub> stub_;
  std::thread hb_thread_;
  bool hb_running_ = false;
  
  IReply Connect();
  IReply List();
  IReply Follow(const std::string &username);
  IReply UnFollow(const std::string &username);
  void   Timeline(const std::string &username);
  void   sendHeartbeat();
};


int Client::connectTo()
{
  std::string addr = hostname + ":" + port;
  stub_ = std::unique_ptr<SNSService::Stub>(SNSService::NewStub(
    grpc::CreateChannel(addr, grpc::InsecureChannelCredentials())));
  
  IReply reply = Connect();
  
  if (!reply.grpc_status.ok()) {
    return -1;
  }
  
  if (reply.comm_status != SUCCESS) {
    return -1;
  }
  
  hb_running_ = true;
  hb_thread_ = std::thread(&Client::sendHeartbeat, this);
  
  return 1;
}

void Client::sendHeartbeat() {
  while (hb_running_) {
    ClientContext ctx;
    google::protobuf::Empty req;
    google::protobuf::Empty rep;
    
    ctx.AddMetadata("username", username);
    stub_->Heartbeat(&ctx, req, &rep);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

IReply Client::processCommand(std::string& input)
{
  IReply ire;
  
  std::size_t idx = input.find_first_of(" ");
  std::string cmd;
  std::string arg;
  
  if (idx != std::string::npos) {
    cmd = input.substr(0, idx);
    arg = input.substr(idx + 1);
  } else {
    cmd = input;
  }
  
  if (cmd == "FOLLOW") {
    ire = Follow(arg);
  } else if (cmd == "UNFOLLOW") {
    ire = UnFollow(arg);
  } else if (cmd == "LIST") {
    ire = List();
  } else if (cmd == "TIMELINE") {
    ire.comm_status = SUCCESS;
    ire.grpc_status = Status::OK;
  } else {
    ire.comm_status = FAILURE_INVALID;
    ire.grpc_status = Status::OK;
  }
  
  return ire;
}


void Client::processTimeline() { 
    Timeline(username);
}

IReply Client::List() {
    IReply ire;
    ClientContext ctx;
    Request req;
    ListReply rep;
    
    req.set_username(username);
    Status status = stub_->List(&ctx, req, &rep);
    
    ire.grpc_status = status;
    
    if (status.ok()) {
      ire.comm_status = SUCCESS;
      
      for (int i = 0; i < rep.all_users_size(); i++) {
        ire.all_users.push_back(rep.all_users(i));
      }
      
      for (int i = 0; i < rep.followers_size(); i++) {
        ire.followers.push_back(rep.followers(i));
      }
    } else {
      ire.comm_status = FAILURE_UNKNOWN;
    }
    
    return ire;
}

IReply Client::Follow(const std::string& u2) {
    IReply ire;
    ClientContext ctx;
    Request req;
    Reply rep;
    
    req.set_username(username);
    req.add_arguments(u2);
    
    Status status = stub_->Follow(&ctx, req, &rep);
    ire.grpc_status = status;
    
    if (status.ok()) {
      std::string msg = rep.msg();
      
      if (msg == "you have already joined") {
        ire.comm_status = FAILURE_ALREADY_EXISTS;
      } else if (msg == "Follow Successful") {
        ire.comm_status = SUCCESS;
      } else if (msg == "user does not exist") {
        ire.comm_status = FAILURE_NOT_EXISTS;
      } else {
        ire.comm_status = FAILURE_UNKNOWN;
      }
    } else {
      ire.comm_status = FAILURE_UNKNOWN;
    }
    
    return ire;
}

IReply Client::UnFollow(const std::string& u2) {
    IReply ire;
    ClientContext ctx;
    Request req;
    Reply rep;
    
    req.set_username(username);
    req.add_arguments(u2);
    
    Status status = stub_->UnFollow(&ctx, req, &rep);
    ire.grpc_status = status;
    
    if (status.ok()) {
      std::string msg = rep.msg();
      
      if (msg == "You are not a follower") {
        ire.comm_status = FAILURE_NOT_A_FOLLOWER;
      } else if (msg == "UnFollow Successful") {
        ire.comm_status = SUCCESS;
      } else {
        ire.comm_status = FAILURE_UNKNOWN;
      }
    } else {
      ire.comm_status = FAILURE_UNKNOWN;
    }
    
    return ire;
}

IReply Client::Connect() {
    IReply ire;
    ClientContext ctx;
    Request req;
    Reply rep;
    
    req.set_username(username);
    Status status = stub_->Connect(&ctx, req, &rep);
    
    ire.grpc_status = status;
    
    if (status.ok()) {
      std::string msg = rep.msg();
      
      if (msg == "you are already connected") {
        ire.comm_status = FAILURE_ALREADY_EXISTS;
      } else if (msg == "Connect Successful") {
        ire.comm_status = SUCCESS;
      } else {
        ire.comm_status = FAILURE_UNKNOWN;
      }
    } else {
      ire.comm_status = FAILURE_UNKNOWN;
    }
    
    return ire;
}

void Client::Timeline(const std::string& u) {
    ClientContext ctx;
    
    std::shared_ptr<ClientReaderWriter<Message, Message>> stream(
      stub_->Timeline(&ctx));
    
    std::thread writer([stream, u, this]() {
      while (1) {
        std::string msg = getPostMessage();
        Message m = MakeMessage(u, msg);
        stream->Write(m);
      }
    });
    
    std::thread reader([stream, this]() {
      Message m;
      while (stream->Read(&m)) {
        std::time_t t = m.timestamp().seconds();
        displayPostMessage(m.username(), m.msg(), t);
      }
    });
    
    writer.join();
    reader.join();
}


//////////////////////////////////////////////
// Main Function
/////////////////////////////////////////////
int main(int argc, char** argv) {

  std::string hostname = "localhost";
  std::string username = "default";
  std::string port = "3010";
    
  int opt = 0;
  while ((opt = getopt(argc, argv, "h:u:p:")) != -1){
    switch(opt) {
    case 'h':
      hostname = optarg;break;
    case 'u':
      username = optarg;break;
    case 'p':
      port = optarg;break;
    default:
      std::cout << "Invalid Command Line Argument\n";
    }
  }
      
  std::cout << "Logging Initialized. Client starting...";
  
  Client myc(hostname, username, port);
  
  myc.run();
  
  return 0;
}