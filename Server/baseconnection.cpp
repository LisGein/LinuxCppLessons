#include "baseconnection.h"
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

namespace
{
    size_t const MAX_MSG_SIZE = 10;
}

void BaseConnection::send_step(const point_t &pos)
{
    std::stringstream msg_stream;
    msg_stream << pos.x << ';' << pos.y;
    std::string msg = msg_stream.str();
    unsigned char size_byte = msg.size();
    msg.insert(msg.begin(), size_byte);

    size_t start = 0;
    while (start != msg.size())
    {
        int len = send(sock_, msg.c_str() + start, msg.size() - start, 0);

        //std::cout << "msg sended: " << std::string(msg.c_str() + start, msg.size() - start) << " len: " << len << std::endl;

        if (len < 0)
        {
            perror("send failed");
            exit(5);
        }

        start += len;
    }
}

point_t BaseConnection::recv_step()
{
    char buf[MAX_MSG_SIZE];
    bool first_recv = true;
    unsigned char size = 0;
    std::string msg;
    do
    {
        //std::cout << "wait fo read" << std::endl;
        int bytes_read = recv(sock_, buf, MAX_MSG_SIZE, 0);
        //std::cout << "msg recived " << std::string(buf, bytes_read) << "len: " << bytes_read << std::endl;
        if (bytes_read < 0)
        {
            perror("recv failed");
            exit(5);
        }

        if (bytes_read == 0)
        {
            std::cout << "Your opponent disconnected" << std::endl;
            exit(0);
        }

        if(first_recv)
        {
            size = buf[0];
            msg.insert(msg.end(), buf + 1, buf + bytes_read);
            first_recv = false;
        }
        else
            msg.insert(msg.end(), buf, buf + bytes_read);

    } while (msg.size() < size);

    std::string temp_mess;
    temp_mess = msg.substr(0, msg.find(";"));
    point_t pos;
    pos.x = atoi (temp_mess.c_str());
    temp_mess = msg.substr(msg.find(";")+1);
    pos.y = atoi (temp_mess.c_str());
    return pos;
}
