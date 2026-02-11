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


#include "client.h"


void IClient::run()
{
  int ret = connectTo();
  if (ret < 0) {
    std::cout << "connection failed: " << ret << std::endl;
    exit(1);
  }
  displayTitle();
  while (1) {
    std::string cmd = getCommand();
    IReply reply = processCommand(cmd);
    displayCommandReply(cmd, reply);
    if (reply.grpc_status.ok() && reply.comm_status == SUCCESS
	&& cmd == "TIMELINE") {
      std::cout << "Now you are in the timeline" << std::endl;
      processTimeline();
    }
  }
}

void IClient::displayTitle() const
{
  std::cout << "\n========= TINY SNS CLIENT =========\n";
  std::cout << " Command Lists and Format:\n";
  std::cout << " FOLLOW <username>\n";
  std::cout << " UNFOLLOW <username>\n";
  std::cout << " LIST\n";
  std::cout << " TIMELINE\n";
  std::cout << "=====================================\n";
}

std::string IClient::getCommand() const
{
  std::string input;
  while (1) {
    std::cout << "Cmd> ";
    std::getline(std::cin, input);
    std::size_t index = input.find_first_of(" ");
    if (index != std::string::npos) {
      std::string cmd = input.substr(0, index);
      toUpperCase(cmd);
      if(input.length() == index+1){
	std::cout << "Invalid Input -- No Arguments Given\n";
	continue;
      }
      std::string argument = input.substr(index+1, (input.length()-index));
      input = cmd + " " + argument;
    } else {
      toUpperCase(input);
      if (input != "LIST" && input != "TIMELINE") {
	std::cout << "Invalid Command\n";
	continue;
      }
    }
    break;
  }
  return input;
}

void IClient::displayCommandReply(const std::string& comm, const IReply& reply) const
{
  if (reply.grpc_status.ok()) {
    switch (reply.comm_status) {
    case SUCCESS:
      std::cout << "Command completed successfully\n";
      if (comm == "LIST") {
	std::cout << "All users: ";
	for (std::string room : reply.all_users) {
	  std::cout << room << ", ";
	}
	std::cout << "\nFollowers: ";
	for (std::string room : reply.followers) {
	  std::cout << room << ", ";
	}
	std::cout << std::endl;
      }
      break;
    case FAILURE_ALREADY_EXISTS:
      std::cout << "Input username already exists, command failed\n";
      break;
    case FAILURE_NOT_EXISTS:
      std::cout << "Input username does not exists, command failed\n";
      break;
    case FAILURE_INVALID_USERNAME:
      std::cout << "Command failed with invalid username\n";
      break;
    case FAILURE_NOT_A_FOLLOWER:
      std::cout << "Command failed with not a follower\n";
      break;     
    case FAILURE_INVALID:
      std::cout << "Command failed with invalid command\n";
      break;
    case FAILURE_UNKNOWN:
      std::cout << "Command failed with unknown reason\n";
      break;
    default:
      std::cout << "Invalid status\n";
      break;
    }
  } else {
    std::cout << "grpc failed: " << reply.grpc_status.error_message() << std::endl;
  }
}

void IClient::toUpperCase(std::string& str) const
{
  std::locale loc;
  for (std::string::size_type i = 0; i < str.size(); i++)
    str[i] = toupper(str[i], loc);
}

/*
 * get/displayPostMessage functions will be called in chatmode
 */
std::string getPostMessage()
{
  char buf[MAX_DATA];
  while (1) {
    fgets(buf, MAX_DATA, stdin);
    if (buf[0] != '\n')  break;
  }

  std::string message(buf);
  return message;
}

void displayPostMessage(const std::string& sender, const std::string& message, std::time_t& time)
{
  std::string t_str(std::ctime(&time));
  t_str[t_str.size()-1] = '\0';
  std::cout << sender << " (" << t_str << ") >> " << message << std::endl;
}

void displayReConnectionMessage(const std::string& host, const std::string & port) {
  std::cout << "Reconnecting to " << host << ":" << port << "..." << std::endl;
}

