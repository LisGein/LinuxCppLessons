#include "networkserver.h"

NetworkServer::NetworkServer(int port)
    :port_(port)
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
    sock_ = accept(listener_, NULL, NULL);
    if(sock_ < 0)
    {
        perror("accept");
        exit(3);
    }
}
NetworkServer::~NetworkServer()
{
}

bool NetworkServer::first_step()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random_range(0, 999);
    char buf[MAX_LEN_RANDOM];
    recv(sock_, buf, 1, 0);
    int op_roll = atoi (buf);
    int my_roll(random_range(gen));
    sprintf(buf, "%d", my_roll);
    send(sock_, &my_roll, 1, 0);
    return my_roll > op_roll;
}
void NetworkServer::send_step(const point_t &pos)
{}

point_t NetworkServer::revc_step()
{
    char messege[buf_.size()];
    bytes_read_ = recv(sock_, messege, sizeof(buf_), 0);
    std::string buf = messege;
    std::string temp_mess;
    temp_mess = buf.substr(0, buf.find(";"));
    point_t pos;
    pos.x = atoi (temp_mess.c_str());
    temp_mess = buf.substr(buf.find(";")+1);
    pos.y = atoi (temp_mess.c_str());
    return pos;
}
