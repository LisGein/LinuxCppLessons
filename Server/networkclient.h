#pragma once
#include "iconnection.h"
#include <random>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "point_t.h"

class NetworkClient
    :public IConnection
{
public:
  NetworkClient(int port);
  ~NetworkClient();
  bool first_turn();
  void send_step(point_t const &input_pos);
  point_t recv_step();
private:
  point_t point_;
  int port_;
  int sock_;
  int listener_;
  int bytes_read_;
  struct sockaddr_in addr_;
  std::string buf_;
  const int MAX_LEN_RANDOM = 1;
};
