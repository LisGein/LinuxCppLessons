#include "networkclient.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>


  NetworkClient::NetworkClient()
  {}
  NetworkClient::~NetworkClient()
  {}
  void NetworkClient::connecting()
  {
    std::cout << "Input your port\n";
    std::cin >> port_;
    std::cout << "Input port second player\n";
    std::cin >> listen_port_;
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
    addr_.sin_port = htons(listen_port_);
    addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "x or o?\n";
    std::cin >> colibrate_sumb_;
    games.set_data(colibrate_sumb_, sock_);
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

  void NetworkClient::send_recv()
  {
    std::string buf;
    if (colibrate_sumb_ == 'o')
    {
      char mes[buf.size()];
      bytes_read_ = recv(sock_server_, mes, sizeof(buf), 0);
      std::string sdr = mes;
      games.send_data(sdr);
      colibrate_sumb_ = 'x';
      std::cout << "\033[2J\033[1;1H";
    }
    games.game();
    char mes[buf.size()];
    bytes_read_ = recv(sock_server_, mes, sizeof(buf), 0);
    //send(sock_server_, buf.c_str(), bytes_read_, 0);
    std::string sdr = mes;
    games.send_data(sdr);
  }

  void NetworkClient::end_connect()
  {
    close(sock_);
    close(sock_server_);
    close(listener_);
  }

