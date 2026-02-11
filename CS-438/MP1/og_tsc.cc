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
  
  IReply Connect();
  IReply List();
  IReply Follow(const std::string &username);
  IReply UnFollow(const std::string &username);
  void   Timeline(const std::string &username);
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
    
  ///////////////////////////////////////////////////////////
  // YOUR CODE HERE
  // login_info = hostname + ":" + port
  // stub_ = new SNSService::Stub(…, login_info, ...)
  // reply = login()
  // if (!reply.status.ok()) {
  //    return –1;
  // }
  //////////////////////////////////////////////////////////

    return 1;
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
    
    /*********
    YOUR CODE HERE
    cmd, arg = split(input)

    if("follow" == cmd){
        Follow(arg)
    }else if("unfollow" == cmd){
        UnFollow(arg)
    }else if("list" == cmd){
        LIST()
    }else if("timeline" == cmd){
        TIMELINE()
    }
    **********/

    return ire;
}


void Client::processTimeline() { 
    Timeline(username);
}

// List Command
IReply Client::List() {

    IReply ire;

    /*********
    YOUR CODE HERE
    Status status = stub_->List(..., request, &list_reply);
    if(status.ok()){
       for u in (all users of list_reply):  
          add u to (ire users)
       for f in (all followers of list_reply):  
          add f to (ire followers)
    **********/

    return ire;
}

// Follow Command        
IReply Client::Follow(const std::string& username2) {

    IReply ire; 
      
    /***
    YOUR CODE HERE
    Status status = stub_->Follow(..., request, &list_reply);
    if(reply.msg() == "you have already joined"){
        Follow failed
    else if(reply.msg() == "Follow Successful"):
        Follow succeeded
    ***/

    return ire;
}

// UNFollow Command  
IReply Client::UnFollow(const std::string& username2) {

    IReply ire;

    /***
    YOUR CODE HERE
    Status status = stub_->UnFollow(..., request, &list_reply);
    if(reply.msg() == "You are not a follower"){
       UnFollow failed
    else if(reply.msg() == "UnFollow Successful"):
       UnFollow succeeded
    ***/

    return ire;
}

// Register function  
IReply Client::Connect() {

    IReply ire;
  
    /***
     YOUR CODE HERE
     Status status = stub_->Login(..., request, &reply);
     if (reply.msg() == "you are already connected") {
         Connection failed;
     } else {
        Connection succeeded;
     }
    ***/

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

  
    /***
    YOUR CODE HERE
    gRPC_RW_Steam stream(stub_->Timeline(...));

    writer_thread([...](){
       while(1){
           stream->writeMessageToStream(terminal_message);
       }
    });

    reader_thread([...](){
       while(stream.read(Message m)){
           displayPostMessage(…, m, timestamp);
       }
    });

    threads_join()
    ***/

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


