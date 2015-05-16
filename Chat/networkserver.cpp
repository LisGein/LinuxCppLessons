#include "networkserver.h"
#include <cstdio>


NetworkServer::NetworkServer()
  :timeout_(-1)
  , id_(2)
  , root_name_("0unknown")
{
  listener_ = socket(AF_INET, SOCK_STREAM, 0);
  if(listener_ < 0)
    {
      perror("socket");
      exit(1);
    }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3325);
  addr.sin_addr.s_addr = INADDR_ANY;
  if(bind(listener_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("bind");
      exit(2);
    }
  listen(listener_, 2);
  memset(fds_, 0 , sizeof(fds_));
  fds_[0].fd = listener_;
  fds_[0].events = POLLIN|POLLOUT;
  fds_[1].fd = STDIN_FILENO;
  fds_[1].events = POLLIN;
  fds_[1].revents = 0;
  std::cout << "Input nick\n"
            << "Your nickname must be less than 12 characters!\n";

}

NetworkServer::~NetworkServer()
{
  close(listener_);
}

void NetworkServer::step()
{
  poll(fds_, id_, timeout_);
  if (fds_[1].revents & POLLIN)
    {
      std::string my_message;
      if (root_name_ == "0unknown")
        {
          do
            {
              std::getline(std::cin, my_message);

            } while(my_message.size() > 12);
          root_name_ = my_message + ": ";
          std::string message = my_message + " connected";
          message_send(message);
        }
      else
        {
          std::getline(std::cin, my_message);
          my_message.insert(my_message.begin(), root_name_.begin(), root_name_.begin()+root_name_.size());
          message_send(my_message);
        }
    }
  else
    {
      if (fds_[0].revents & POLLIN)
        add_user();

      for (int i = 1; i < id_; i++)
        if (fds_[i].revents & POLLIN)
          {
            buf_[BUFFER_SIZE] = '\n';
            bytes_read_ = read(fds_[i].fd, buf_, BUFFER_SIZE);
            if (bytes_read_ == 0)
              {
                std::string client_nick= clients_[fds_[i].fd] + " disconected";
                std::cout << client_nick << std::endl;
                close(fds_[i].fd);
                fds_[i].fd = -1;
                clients_.erase(fds_[i].fd);
              }
            start = buf_;
            while (bytes_read_ > 0)
                message_read(i);
          }
    }
}

void NetworkServer::add_user()
{
  int sock = accept(listener_, NULL, NULL);
  fds_[id_].fd = sock;
  fds_[id_].events = POLLIN|POLLOUT;
  fds_[id_].revents = 0;
  std::string temp_nick = "0unknown";
  clients_[sock] = temp_nick;
  id_++;
}

void NetworkServer::message_send(std::string &my_msg)
{
  std::cout << my_msg << std::endl;
  for (std::map<int, std::string>::iterator is=clients_.begin(); is!=clients_.end(); ++is)
      send(is->first, my_msg.c_str(), my_msg.size() + 1, 0);
}

void NetworkServer::message_read(int &i)
{
  int len_msg =  strlen(start);
  size_t msg_len = std::min(bytes_read_, len_msg); //мин из размера пришедшего сообщения и сообщения в буфере до \0
  std::string & my_msg = clients_messages_[fds_[i].fd]; //ссылка(!) для сокращения записи
  my_msg.insert(my_msg.end(), start, start + msg_len);
  if (len_msg+1 <= bytes_read_) // нашли 0
    {
      if (clients_[fds_[i].fd] == "0unknown")
        add_nick(i, my_msg);
      else
        forming_send(i, my_msg);
      my_msg.clear();
      start += msg_len + 1;
      bytes_read_ -= msg_len + 1;
    }
  else
    {
      start += msg_len;
      bytes_read_ -= msg_len;
    }
}

void NetworkServer::add_nick(int &i, std::string & my_msg)
{
  clients_[fds_[i].fd] = my_msg;
  std::string message = my_msg + " connected";
  message_send(message);
}

void NetworkServer::forming_send(int &i, std::string & my_msg)
{
  std::string client_nick= clients_[fds_[i].fd] + ": ";
  my_msg.insert(my_msg.begin(), client_nick.begin(), client_nick.begin()+client_nick.size());
  message_send(my_msg);
}