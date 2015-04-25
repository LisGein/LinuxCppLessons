#pragma once
#include "iconnection.h"
#include <random>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include "point_t.h"

class NetworkServer
    :public IConnection
{
public:
  NetworkServer(int port);
  ~NetworkServer();
  bool first_turn();
  void send_step(point_t const &input_pos);
  point_t recv_step();
private:
  int port_;
  int sock_, sock_list_;
  int listener_;
  int bytes_read_;
  struct sockaddr_in addr_;
  std::string buf_;
  const int MAX_LEN_RANDOM = 2;
};

