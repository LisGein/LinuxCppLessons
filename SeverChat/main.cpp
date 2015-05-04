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

typedef std::pair<int, std::string> pairMap;
typedef std::pair<unsigned char, std::string> pairMapMess;

int main()
{
  int listener_;
  int bytes_read_;

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
  pollfd fds_[10];
  memset(fds_, 0 , sizeof(fds_));
  fds_[0].fd = listener_;
  fds_[0].events = POLLIN;
  std::map <int, std::string> clients_;
  int timeout_ = -1;

  int id_ = 1;


  while(true)
    {
      poll(fds_, id_, timeout_);
      if (fds_[0].revents & POLLIN)
        {
          int sock = accept(listener_, NULL, NULL);
          fds_[id_].fd = sock;
          fds_[id_].events = POLLIN||POLLOUT;
          fds_[id_].revents = 0;
          std::string nameUser = "unknown";
          pairMap tempPair = std::make_pair(sock, nameUser);
          clients_.insert(tempPair);
          id_++;
          std::cout << "connected\n";
        }
      for (int it = 0; it < id_; it++)
        {
          if (fds_[it].revents & POLLIN)
            {
              char buf_[100];
              bytes_read_ = recv(fds_[it].fd, buf_, 100, 0);
              if(bytes_read_ > 0)
                {

                  std::string msg_;
                  msg_.insert(msg_.end(), buf_, buf_ + bytes_read_);

                  std::string messageSend = msg_;

                  std::cout << messageSend;
                  unsigned char size_byte = messageSend.size();
                  messageSend.insert(messageSend.begin(), size_byte);
                  for (std::map<int, std::string>::iterator is=clients_.begin(); is!=clients_.end(); ++is)
                    {
                      send(is->first, messageSend.c_str(), messageSend.size()+1, 0);
                    }
                }
            }
        }
    }
  close(listener_);
  return 0;
}
