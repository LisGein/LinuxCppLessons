#include <netinet/in.h>
#include <stdio.h>//for perror
#include <unistd.h>//for close sock
#include <fcntl.h>//for non-block
#include <algorithm>//for exit
#include <map>
#include <sys/poll.h>
#include <iostream>//for input&output
#include <cstring>//for memset
#include <utility>//for pair

const size_t BUFFER_SIZE = 100;

class Chat
{
public:
  Chat()
    :timeout_(-1)
    , id_(1)
  {
    listener_ = socket(AF_INET, SOCK_STREAM, 0);
    if(listener_ < 0)
      {
        perror("socket");
        exit(1);
      }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
      {
        perror("bind");
        exit(2);
      }
    listen(listener_, 2);
    memset(fds_, 0 , sizeof(fds_));
    fds_[0].fd = listener_;
    fds_[0].events = POLLIN;
  }
  ~Chat()
  {
    close(listener_);
  }
  void step()
  {
    poll(fds_, id_, timeout_);
    if (fds_[0].revents & POLLIN)
      add_user();

    for (int i = 1; i < id_; i++)
      if (fds_[i].revents & POLLIN)
        {
          buf_[BUFFER_SIZE] = '\0';
          bytes_read_ = recv(fds_[i].fd, buf_, BUFFER_SIZE, 0);

          start = buf_;
          while (bytes_read_ > 0)
            {
              message_recv(i);
            }
        }
  }
private:
  void add_user()
  {
    int sock = accept(listener_, NULL, NULL);
    fds_[id_].fd = sock;
    fds_[id_].events = POLLIN||POLLOUT;
    fds_[id_].revents = 0;
    std::string nameUser = "unknown";
    clients_[sock] = nameUser;
    id_++;
    std::cout << "connected\n";

  }

  void message_send(std::string &my_msg)
  {
    for (std::map<int, std::string>::iterator is=clients_.begin(); is!=clients_.end(); ++is)
      {
        send(is->first, my_msg.c_str(), my_msg.size()+1, 0);
      }
  }

  void message_recv(int &i)
  {

    int len_msg = strlen(start);
    size_t msg_len = std::min(bytes_read_, len_msg); //мин из размера пришедшего сообщения и сообщения в буфере до \0
    std::string & my_msg = clients_messages_[fds_[i].fd]; //ссылка(!) для сокращения записи
    my_msg.insert(my_msg.begin(), start, start + msg_len);
    if (len_msg+1 <= bytes_read_) // нашли 0
      {
        std::cout << my_msg << std::endl;
        message_send(my_msg);
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

  int listener_;
  pollfd fds_[10];//ак сделать самоувеличивающийся
  std::map <int, std::string> clients_;
  int timeout_;
  int id_;
  std::map<int, std::string> clients_messages_;
  int bytes_read_;
  char buf_[BUFFER_SIZE + 1];
  std::string msg_;
  std::string messageSend;
  char * start;
};

int main()
{
  Chat chat;
  while(true)
    chat.step();

  return 0;
}
