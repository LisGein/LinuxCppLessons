#include "networkclient.h"


NetworkClient::NetworkClient(int port)
    :port_(port)
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_ < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port_);
    addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
    {
        perror("connect");
        exit(2);
    }
}

NetworkClient::~NetworkClient()
{
    close(sock_);
}

bool NetworkClient::first_turn()
{
    return true;
    char op_roll;
    int len = recv(sock_, &op_roll, 1, 0);
    std::cout << "first recv returns " << len << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random_range(0, 255);
    char my_roll = random_range(gen);
    send(sock_, &my_roll, 1, 0);

    return my_roll > op_roll;

}



