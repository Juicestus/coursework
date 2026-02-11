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
#include <string>
#include <ctime>
#include <vector>
#include <grpc++/grpc++.h>

#define MAX_DATA 256

enum IStatus
{
    SUCCESS,
    FAILURE_ALREADY_EXISTS,
    FAILURE_NOT_EXISTS,
    FAILURE_INVALID_USERNAME,
    FAILURE_NOT_A_FOLLOWER,
    FAILURE_INVALID,
    FAILURE_UNKNOWN
};

/*
 * IReply structure is designed to be used for displaying the
 * result of the command that has been sent to the server.
 * For example, in the "processCommand" function, you should
 * declare a variable of IReply structure and set based on
 * the type of command and the result.
 *
 * - FOLLOW/UNFOLLOW/TIMELINE command:
 * IReply ireply;
 * ireply.grpc_status = return value of a service method
 * ireply.comm_status = one of values in IStatus enum
 *
 * - LIST command:
 * IReply ireply;
 * ireply.grpc_status = return value of a service method
 * ireply.comm_status = one of values in IStatus enum
 * reply.users = list of all users who connected to the server at least onece
 * reply.followers = list of users who following current user;
 *
 * This structure is not for communicating between server and client.
 * You need to design your own rules for the communication.
 */
struct IReply
{
    grpc::Status grpc_status;
    enum IStatus comm_status;
    std::vector<std::string> all_users;
    std::vector<std::string> followers;
};


std::string getPostMessage();
void displayPostMessage(const std::string& sender, const std::string& message, std::time_t& time);
  
class IClient
{
public:
  void run();
  
protected:
  /*
   * Pure virtual functions to be implemented by students
   */
  virtual int connectTo() = 0;
  virtual IReply processCommand(std::string& cmd) = 0;
  virtual void processTimeline() = 0;
  
private:
  void displayTitle() const;
  std::string getCommand() const;
  void displayCommandReply(const std::string& comm, const IReply& reply) const;
  void toUpperCase(std::string& str) const;
};



