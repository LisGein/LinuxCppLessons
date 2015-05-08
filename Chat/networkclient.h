#pragma once
#include "baseconnection.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/poll.h>
#include <map>
#include <cstring>

class NetworkClient
    :public BaseConnection
{
public:
  NetworkClient();
  ~NetworkClient();
    void step();
private:
    void message_send();
    void message_read();

    int sock_;
    std::string user_name_;
    pollfd fds_[2];
    int timeout_;
    int bytes_read_;
    char buf_[BUFFER_SIZE + 1];
    char * start;
    std::string incoming_messages_;
    std::string my_message_;
};


