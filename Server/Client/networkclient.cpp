#include "networkclient.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cctype>

  NetworkClient::NetworkClient()

  {}
  NetworkClient::~NetworkClient()
  {
    close(sock_);
    close(sock_server_);
    close(listener_);
  }

  void NetworkClient::create_serv(int &port_)
  {
    listener_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_ < 0)
    {
      perror("socket");
      exit(1);
    }
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port_);
    addr_.sin_addr.s_addr = INADDR_ANY;
    if (bind(listener_, (struct sockaddr *)&addr_, sizeof(addr_))<0)
    {
      perror("bind");
      exit(2);
    }
    listen(listener_, 2);
    addr_.sin_family = AF_INET;
  }

  void NetworkClient::create_connect(int &listen_port_)
  {
    addr_.sin_port = htons(listen_port_);
    addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_ < 0)
    {
      perror("socket");
      exit(1);
    }
    if(connect(sock_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
    {
      perror ("connect");
      exit(2);
    }
    sock_server_ = accept(listener_, NULL, NULL);
    if(sock_server_ < 0)
    {
      perror("accept");
      exit(3);
    }
  }

  int NetworkClient::return_sock()
  {
    return sock_;
  }

  char NetworkClient::selection_first_player(int &random_numb)
  {
    char buf[MAX_LEN_RANDOM];
    sprintf(buf, "%d", random_numb);
    send(sock_, buf, MAX_LEN_RANDOM, 0);
    recv(sock_server_, buf, sizeof(buf), 0);
    int random_oponent = atoi (buf);
    if (random_numb > random_oponent)
       player_symb_ = 'x';
    else
       player_symb_ = 'o';
    return player_symb_;
  }

  void NetworkClient::send_data(std::string &input_pos, std::string &finish_game)
  {
    send(sock_, input_pos.c_str(), input_pos.size() + 1, 0);
    send(sock_, finish_game.c_str(), finish_game.size() + 1, 0);
  }

  std::string NetworkClient::recv_data()
  {
    char mes[buf_.size()];
    bytes_read_ = recv(sock_server_, mes, sizeof(buf_), 0);
    std::string messege = mes;
    return messege;
  }
