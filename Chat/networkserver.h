#pragma once
#include <netinet/in.h>
#include <stdio.h>//for perror
#include <unistd.h>//for close sock
#include <algorithm>//for exit
#include <map>
#include <sys/poll.h>
#include <iostream>//for input&output
#include <cstring>//for memset
#include <utility>//for pair
#include "baseconnection.h"


class NetworkServer
    :public BaseConnection
{
public:
  NetworkServer();
  ~NetworkServer();
  void step();
private:
  void add_user();
  void add_nick(int &i, std::string & my_msg);
  void message_send(std::string &my_msg);
  void message_read(int &i);
  void forming_send(int &i, std::string & my_msg);

  int listener_;
  pollfd fds_[10];//как сделать самоувеличивающийся
  std::map <int, std::string> clients_;
  int timeout_;
  int id_;
  std::map<int, std::string> clients_messages_;
  int bytes_read_;
  char buf_[BUFFER_SIZE + 1];
  std::string root_name_;
  char * start;
};

