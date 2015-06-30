#pragma once
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

class NetworkServer
        :public BaseConnection
{
public:
    NetworkServer(int port);
    ~NetworkServer();
    bool first_turn();
    void send_step(point_t const &input_pos);
    point_t recv_step();
private:
    int port_;
    int listener_;
    int bytes_read_;
};

