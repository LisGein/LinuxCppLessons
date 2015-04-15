#pragma once
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


