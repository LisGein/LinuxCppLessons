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
  bool first_step();
  void send_step(std::string &input_pos);
  point_t revc_step();
private:
  Point_t point_t;
  int port_;
  int sock_;
  int listener_;
  int bytes_read_;
  struct sockaddr_in addr_;
  std::string buf_;
  const int MAX_LEN_RANDOM = 1;
};

