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
  bool first_step();
  void send_step(const point_t &pos);
  point_t revc_step();
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








/*
#include "games.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
class NetworkClient
{
private:
  Games games;
  int port_;
  char colibrate_sumb_;
  int sock_server_, listener_;
  int bytes_read_;
  int listen_port_;
  struct sockaddr_in addr_;
  int sock_;

public:
  NetworkClient();
  ~NetworkClient();
  void connecting();
  void send_recv();
  void end_connect();
};
*/
