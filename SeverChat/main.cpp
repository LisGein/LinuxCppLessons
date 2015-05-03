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

int main()
{
  int listener;
  struct sockaddr_in addr;
  int bytes_read;

  listener = socket(AF_INET, SOCK_STREAM, 0);
  if(listener < 0)
    {
      perror("socket");
      exit(1);
    }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = INADDR_ANY;
  if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("bind");
      exit(2);
    }

  listen(listener, 2);
  //fcntl(listener, F_SETFL, O_NONBLOCK);

  pollfd fds[4];
  int nfds = 10;
  memset(fds, 0 , sizeof(fds));
  fds[0].fd = listener;
  fds[0].events = POLLIN;
  std::map <int, std::string> clients;
  clients.clear();
  int timeout = -1;
  pairMap tempPair;
  int id = 0;
  while(true)
    {
      //if(
         poll(fds, nfds, timeout);//<= 0)
       // {
        //  perror("  poll() failed");
         // exit(3);
       //}
      if (fds[0].revents & POLLIN)
        {
          int sock = accept(listener, NULL, NULL);
          id++;
          fds[id].fd = sock;
          fds[id].events = POLLIN||POLLOUT;
          fds[id].revents = 0;
          std::string nameUser = "unknown";
          tempPair = std::make_pair(sock, nameUser);
          clients.insert(tempPair);
          std::cout << "connected\n";
        }
      char buf[10];
      bool first_recv;
      unsigned char size;
      for (int it = 1; it < nfds; it++)
         {
          if (fds[it].revents & POLLIN)
            {
              first_recv = true;
              size = 0;
              std::string msg;
              bytes_read = recv(fds[it].fd, buf, 10, 0);
              if(bytes_read > 0)
                {
                  do
                    {
                      if(first_recv)
                        {
                          size = buf[0];
                          msg.insert(msg.end(), buf + 1, buf + bytes_read);
                          first_recv = false;
                        }
                      else
                        msg.insert(msg.end(), buf, buf + bytes_read);
                    } while (msg.size() < size);

                  std::string msg1 = clients.find(fds[it].fd)->second + ": " +
                      msg + "\n";

                  std::cout << msg1;
                  unsigned char size_byte = msg1.size();
                  msg1.insert(msg1.begin(), size_byte);

                  size_t start = 0;
                  for (std::map<int, std::string>::iterator is=clients.begin(); is!=clients.end(); ++is)
                    {
                      while (start != msg1.size())
                        {
                          int len = send(is->first, msg1.c_str() + start, msg1.size() - start, 0);
                          if (len < 0)
                            {
                              perror("send failed");
                              exit(5);
                            }

                          start += len;
                        }
                    }
                }
            }
        }
    }
  close(listener);
  return 0;
}
