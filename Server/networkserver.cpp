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

  std::cout <<"You oponent connected? \n";
  std::string input_start;
  std::cin >> input_start;
  sock_list_ = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_list_ < 0)
    {
      perror("socket");
      exit(1);
    }
  if(connect(sock_list_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
    {
      perror ("connect");
      exit(2);
    }
  sock_list_ = accept(listener_, NULL, NULL);
  if(sock_list_ < 0)
    {
      perror("accept");
      exit(3);
    }
}

NetworkServer::~NetworkServer()
{
  close(sock_);
  close(sock_list_);
  close(listener_);
}

bool NetworkServer::first_turn()
{
  bool uniform_random = true;
  int my_roll;
  int op_roll;
  while (uniform_random)
    {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<int> random_range(0, 9);
      int rand_roll(random_range(gen));
      my_roll = rand_roll;
      char msg[MAX_LEN_RANDOM];
      msg[0] = rand_roll + '0';
      msg[1] += 0;
      send(sock_list_, &msg, MAX_LEN_RANDOM, 0);
      char buf[MAX_LEN_RANDOM];
      recv(sock_list_, buf,  MAX_LEN_RANDOM, 0);
      op_roll = atoi (buf);
      if (my_roll != op_roll)
        uniform_random = false;
    }
  return my_roll > op_roll;
}

void NetworkServer::send_step(point_t const &input_pos)//зачем пересылать pos и преобраовывать, вместо того, чтобы
{                                                       //послать messadge для меня до сих пор загадка
  std::string message_send;
  char buf[MAX_LEN_RANDOM];
  sprintf(buf, "%d", input_pos.x);
  message_send = buf;
  sprintf(buf, "%d", input_pos.y);
  message_send += ";";
  message_send += buf;
  send(sock_list_, message_send.c_str(), message_send.size() + 1, 0);
}

point_t  NetworkServer::recv_step()
{
  char messege[buf_.size()];
  bytes_read_ = recv(sock_list_, messege, sizeof(buf_), 0);
  std::string buf = messege;
  std::string temp_mess;
  temp_mess = buf.substr(0, buf.find(";"));
  point_t pos;
  pos.x = atoi (temp_mess.c_str());
  temp_mess = buf.substr(buf.find(";")+1);
  pos.y = atoi (temp_mess.c_str());
  return pos;
}
