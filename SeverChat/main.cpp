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
  fcntl(listener, F_SETFL, O_NONBLOCK);

  struct pollfd fds[4];
  int nfds = 1;
  memset(fds, 0 , sizeof(fds));
  fds[0].fd = listener;
  fds[0].events = POLLIN;
  std::map <int, std::string> clients;
  clients.clear();
  int timeout = -1;
  pairMap tempPair;
  if(poll(fds, nfds, timeout) <= 0)
    {
      perror("  poll() failed");
      exit(3);
    }
  while(true)
    {
      if (fds[0].revents & POLLIN)
        {
          int sock = accept(listener, NULL, NULL);
          if(sock >= 0)
            {
              char nickName[100];
              bytes_read = recv(sock , nickName, 100, 0);
              bool first_recv = true;
              unsigned char size = 0;
              std::string nameUser;
              do
                {
                  if(first_recv)
                    {
                      size = nickName[0];
                      nameUser.insert(nameUser.end(), nickName + 1, nickName + bytes_read);
                      first_recv = false;
                    }
                  else
                    nameUser.insert(nameUser.end(), nickName, nickName + bytes_read);
                } while (nameUser.size() < size);


              std::string message = nameUser + " connected.\n";
              std::cout << message;

              if (!clients.empty())
                {
                  unsigned char size_byte = message.size();
                  message.insert(message.begin(), size_byte);

                  size_t start = 0;
                  for (std::map<int, std::string>::iterator is=clients.begin(); is!=clients.end(); ++is)
                    {

                      while (start != message.size())
                        {
                          int len = send(is->first, message.c_str() + start, message.size() - start, 0);
                          if (len < 0)
                            {
                              perror("send failed");
                              exit(5);
                            }

                          start += len;
                        }
                    }
                }
              tempPair = std::make_pair(sock, nameUser);
              clients.insert(tempPair);
              //std::string messageHello = "Welcome to chat!\n";
              //send(sock, messageHello.c_str(), messageHello.size(), 0);
              fcntl(sock, F_SETFL, O_NONBLOCK);
            }
        }
      for (std::map<int, std::string>::iterator it=clients.begin(); it!=clients.end(); ++it)
        {
          char buf[10];
          bool first_recv = true;
          unsigned char size = 0;
          std::string msg;
          bytes_read = recv(it->first, buf, 10, 0);
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

              //std::stringstream msg_stream;
              //msg_stream << it->second << ': ' << msg <<'\n'; - при таком варианте в строке : заменялось на 1488
              std::string msg1 = it->second + ": " + msg + "\n";
              //msg_stream.str();
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
  for (std::map<int, std::string>::iterator is=clients.begin(); is!=clients.end(); ++is)
    close(is->first);//надо сделать закрытие при выходе клиента

  close(listener);
  return 0;
}
