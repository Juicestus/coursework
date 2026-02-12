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
  
  // You can have an instance of the client stub
  // as a member variable.
  std::unique_ptr<SNSService::Stub> stub_;

  std::thread heartbeatSender;
  bool sendingHeartbeat = false;
  
  IReply Connect();
  IReply List();
  IReply Follow(const std::string &username);
  IReply UnFollow(const std::string &username);
  void   Timeline(const std::string &username);

  void sendHeartbeat();
};


///////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////
int Client::connectTo()
{
  // ------------------------------------------------------------
  // In this function, you are supposed to create a stub so that
  // you call service methods in the processCommand/porcessTimeline
  // functions. That is, the stub should be accessible when you want
  // to call any service methods in those functions.
  // Please refer to gRpc tutorial how to create a stub.
  // ------------------------------------------------------------
    
  // login_info = hostname + ":" + port
  std::string login_info = hostname + ":" + port;
  // stub_ = new SNSService::Stub(…, login_info, ...)
  stub_ = std::unique_ptr<SNSService::Stub>(SNSService::NewStub(
    grpc::CreateChannel(login_info, grpc::InsecureChannelCredentials())
  ));
  // reply = login()
  IReply reply = Connect();
  // if (!reply.status.ok()) {
  if (!reply.grpc_status.ok()) { return -1; }
  //    return –1;
  // }
  if (reply.comm_status != SUCCESS) { return -1; }

  sendingHeartbeat = true;
  heartbeatSender = std::thread(&Client::sendHeartbeat, this);
  return 1;
}

void Client::sendHeartbeat()
{
  while (sendingHeartbeat) {
    ClientContext ctx;
    google::protobuf::Empty req;
    google::protobuf::Empty rep;

    ctx.AddMetadata("username", username);
    stub_->Heartbeat(&ctx, req, &rep);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  }
}

IReply Client::processCommand(std::string& input)
{
  // ------------------------------------------------------------
  // GUIDE 1:
  // In this function, you are supposed to parse the given input
  // command and create your own message so that you call an 
  // appropriate service method. The input command will be one
  // of the followings:
  //
  // FOLLOW <username>
  // UNFOLLOW <username>
  // LIST
  // TIMELINE
  // ------------------------------------------------------------
  
  // ------------------------------------------------------------
  // GUIDE 2:
  // Then, you should create a variable of IReply structure
  // provided by the client.h and initialize it according to
  // the result. Finally you can finish this function by returning
  // the IReply.
  // ------------------------------------------------------------
  
  
  /** ------------------------------------------------------------
   HINT: How to set the IReply?
   Suppose you have "FOLLOW" service method for FOLLOW command,
   IReply can be set as follow:
   
       IReply ire;
       grpc::Status status = stub_->FOLLOW(&context, ... some parameters ... );
       ire.grpc_status = status;
       if (status.ok()) {
           ire.comm_status = SUCCESS;
       } else {
           ire.comm_status = FAILURE_NOT_EXISTS;
       }
        
        return ire;
   
   IMPORTANT: 
   For the command "LIST", you should set both "all_users" and 
   "following_users" member variable of IReply.
   ------------------------------------------------------------
   */

    IReply ire;

    size_t i = input.find_first_of(" ");
    std::string cmd, arg;
    if (i != std::string::npos) {
      cmd = input.substr(0, i);
      arg = input.substr(i + 1);
    } else {
      cmd = input;
    }

    std::cout << cmd << " " << arg << "\n";
    

    if ("FOLLOW" == cmd) {
      ire = Follow(arg);
    } else if("UNFOLLOW" == cmd) {
      ire = UnFollow(arg);
    } else if("LIST" == cmd) {
      ire = List();
    } else if("TIMELINE" == cmd) {
      // ire = Timeline();
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

// List Command
IReply Client::List() {

    IReply ire;

    ClientContext ctx;
    Request req;
    ListReply rep;

    // Status status = stub_->List(..., request, &list_reply);
    req.set_username(username);
    Status status = stub_->List(&ctx, req, &rep);
    ire.grpc_status = status;
    if (status.ok()) {
      ire.comm_status = SUCCESS;
    //    for u in (all users of list_reply):  
      for (int i = 0; i < rep.all_users_size(); i++) {
    //       add u to (ire users)
        ire.all_users.push_back(rep.all_users(i));
      }
    //    for f in (all followers of list_reply):  
      for (int i = 0; i < rep.followers_size(); i++) {
    //       add f to (ire followers)
        ire.followers.push_back(rep.followers(i));
      }
    } else {
      ire.comm_status = FAILURE_UNKNOWN;
    }

    return ire;
}

// Follow Command        
IReply Client::Follow(const std::string& username2) {

    IReply ire; 
    ClientContext ctx;
    Request req;
    Reply reply;

    req.set_username(username);
    req.add_arguments(username2);
      
    // Status status = stub_->Follow(..., request, &list_reply);
    Status status = stub_->Follow(&ctx, req, &reply);
    ire.grpc_status = status;

    // switching based on the message is sus
    if (status.ok()) {
      if (reply.msg() == "you have already joined") {
      //     Follow failed
        ire.comm_status = FAILURE_ALREADY_EXISTS;
      } else if (reply.msg() == "you cannot follow yourself") {
        ire.comm_status = FAILURE_INVALID_USERNAME;
      } else if (reply.msg() == "Follow Successful") {
        ire.comm_status = SUCCESS;
      } else if (reply.msg() == "user does not exist") {
        ire.comm_status = FAILURE_NOT_EXISTS;
      } else {
        ire.comm_status = FAILURE_UNKNOWN;
      }
    } else {
      ire.comm_status = FAILURE_UNKNOWN;
    }

    //     Follow succeeded

    return ire;
}

// UNFollow Command  
IReply Client::UnFollow(const std::string& username2) {

    IReply ire;
    ClientContext ctx;
    Request req;
    Reply reply;

    req.set_username(username);
    req.add_arguments(username2);

    // Status status = stub_->UnFollow(..., request, &list_reply);
    Status status = stub_->UnFollow(&ctx, req, &reply);
    ire.grpc_status = status;
    if (status.ok()) {
      if (reply.msg() == "You are not a follower") {
        //  UnFollow failed
        ire.comm_status = FAILURE_NOT_A_FOLLOWER;
      } else if(reply.msg() == "UnFollow Successful") {
      //    UnFollow succeeded
        ire.comm_status = SUCCESS;
      } else {
        ire.comm_status = FAILURE_UNKNOWN;
      }
    }

    return ire;
}

// Register function  
IReply Client::Connect() {

    IReply ire;
    ClientContext ctx;
    Request req;
    Reply reply;
    req.set_username(username);
  
    //  Status status = stub_->Login(..., request, &reply);
    Status status = stub_->Connect(&ctx, req, &reply);
    ire.grpc_status = status;
    if (status.ok()) {
      if (reply.msg() == "you are already connected") {
        //  Connection failed;
        ire.comm_status = FAILURE_ALREADY_EXISTS;
      } else if (reply.msg() == "Connection Successful") {
        ire.comm_status = SUCCESS;
      } else {
      //     Connection succeeded;
        ire.comm_status = FAILURE_UNKNOWN;
      }
    } else {
      ire.comm_status = FAILURE_UNKNOWN;
    }

    return ire;
}

// Timeline Command
void Client::Timeline(const std::string& username) {

    // ------------------------------------------------------------
    // In this function, you are supposed to get into timeline mode.
    // You may need to call a service method to communicate with
    // the server. Use getPostMessage/displayPostMessage functions 
    // in client.cc file for both getting and displaying messages 
    // in timeline mode.
    // ------------------------------------------------------------

  
    ClientContext ctx;
    // gRPC_RW_Steam stream(stub_->Timeline(...));
    std::shared_ptr<ClientReaderWriter<Message, Message>> stream(stub_->Timeline(&ctx));

    stream->Write(MakeMessage(username, ""));

    // writer_thread([...](){
    //    while(1){
    //        stream->writeMessageToStream(terminal_message);
    //    }
    // });
    std::thread writer_thread([stream, username, this]() {
      while (true) {
        std::string pm = getPostMessage();
        if (!pm.empty()) {
          stream->Write(MakeMessage(username, pm));
        }
      }
    });

    // reader_thread([...](){
    //    while(stream.read(Message m)){
    //        displayPostMessage(…, m, timestamp);
    //    }
    // });
    std::thread reader_thread([stream, this]() {
      Message m;
      while (stream->Read(&m)) {
        time_t timestamp = (time_t)m.timestamp().seconds();
        displayPostMessage(m.username(), m.msg(), timestamp);
      }
    });

    // threads_join()
    writer_thread.join();
    reader_thread.join();

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


