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
      char buf[MAX_LEN_RANDOM];
      recv(sock_, buf, MAX_LEN_RANDOM, 0);
      op_roll = atoi (buf);
      send(sock_, &msg, MAX_LEN_RANDOM, 0);
      if (my_roll != op_roll)
        uniform_random = false;
    }
  return my_roll > op_roll;
}

void NetworkClient::send_step(point_t const &input_pos)//зачем пересылать pos и преобраовывать, вместо того, чтобы
{                                                       //послать messadge для меня до сих пор загадка
  std::string message_send;
  char buf[MAX_LEN_RANDOM];
  sprintf(buf, "%d", input_pos.x);
  message_send = buf;
  sprintf(buf, "%d", input_pos.y);
  message_send += ";";
  message_send += buf;
  send(sock_, message_send.c_str(), message_send.size() + 1, 0);
}

point_t NetworkClient::recv_step()
{
  char message[buf_.size()];
  bytes_read_ = recv(sock_, message, sizeof(buf_), 0);
  std::string buf = message;
  std::string temp_mess;
  temp_mess = buf.substr(0, buf.find(";"));
  point_t pos;
  pos.x = atoi (temp_mess.c_str());
  temp_mess = buf.substr(buf.find(";")+1);
  pos.y = atoi (temp_mess.c_str());
  return pos;
}



