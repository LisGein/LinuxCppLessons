#include "networkclient.h"

NetworkClient::NetworkClient()
  :timeout_(-1)
  , user_name_("0unknown")
{
  sock_ = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_ < 0)
    {
      perror("socket");
      exit(1);
    }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  if(connect(sock_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("connect");
      exit(2);
    }
  memset(fds_, 0 , sizeof(fds_));
  fds_[0].fd = sock_;
  fds_[0].events = POLLIN|POLLOUT;
  fds_[1].fd = STDIN_FILENO;
  fds_[1].events = POLLIN;
  fds_[1].revents = 0;
  std::cout << "Input nick\n"
            << "Your nickname must be less than 12 characters!\n";

}

NetworkClient::~NetworkClient()
{
  close(sock_);
}

void NetworkClient::step()
{
  poll(fds_, 2, timeout_);
  if (fds_[1].revents & POLLIN)
    {
      std::string nick;
      if (user_name_ == "0unknown")
        {
          do
            {
              std::getline(std::cin, nick);
            }while(nick.size() > 12);
          user_name_ = nick + ": ";
          my_message_ = nick;
          message_send();
        }
      else
        {
          std::getline(std::cin, my_message_);
          message_send();
        }
    }
  if (fds_[0].revents & POLLIN)
    {
      buf_[BUFFER_SIZE] = '\n';
      bytes_read_ = read(sock_, buf_, BUFFER_SIZE);

      start = buf_;
      while (bytes_read_ > 0)
          message_read();
    }
}
void NetworkClient::message_send()
{
  send(sock_, my_message_.c_str(), my_message_.size() + 1, 0);
  my_message_.clear();
}

void NetworkClient::message_read()
{
  int len_msg =  strlen(start);
  size_t msg_len = std::min(bytes_read_, len_msg); //мин из размера пришедшего сообщения и сообщения в буфере до \0
  incoming_messages_.insert(incoming_messages_.end(), start, start + msg_len);
  if (len_msg+1 <= bytes_read_) // нашли 0
    {
      std::cout << incoming_messages_ << std::endl;
      incoming_messages_.clear();
      start += msg_len + 1;
      bytes_read_ -= msg_len + 1;
    }
  else
    {
      start += msg_len;
      bytes_read_ -= msg_len;
    }
}
