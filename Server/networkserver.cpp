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

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = INADDR_ANY;

    int yes = 1;
    if ( setsockopt(listener_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
    {
        perror("setsockopt");
        exit(7);
    }

    if (bind(listener_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }
    listen(listener_, 1);

    sock_ = accept(listener_, NULL, NULL);
    if(sock_ < 0)
    {
        perror("accept");
        exit(3);
    }

    std::cout <<"You oponent connected.\n";
}

NetworkServer::~NetworkServer()
{
    close(sock_);
    close(listener_);
}

bool NetworkServer::first_turn()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random_range(0, 128);
    char my_roll = random_range(gen);
    send(sock_, &my_roll, 1, 0);

    char op_roll;
    recv(sock_, &op_roll, 1, 0);
    return my_roll-0 > op_roll-0;
}

