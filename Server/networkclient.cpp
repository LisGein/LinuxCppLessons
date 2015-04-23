#include "networkclient.h"


NetworkClient::NetworkClient(int port)
  :port_(port)
{
  int sock_;
      struct sockaddr_in addr_;

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
{}
bool NetworkClient::first_step()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> random_range(0, 999);
  char buf[MAX_LEN_RANDOM];
  int my_roll(random_range(gen));
  sprintf(buf, "%d", my_roll);
  send(sock_, &my_roll, 1, 0);
  recv(sock_, buf, 1, 0);
  int op_roll = atoi (buf);
  return my_roll > op_roll;

}
void NetworkClient::send_step(point_t const & pos)
{
  std::string msg;
  // сериализация pos должна быть тут
  send(sock_, msg.c_str(), msg.size() + 1, 0);
}
point_t NetworkClient::revc_step()
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



