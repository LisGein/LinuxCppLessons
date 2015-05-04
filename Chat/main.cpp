#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <unistd.h>//for close sock


int main()
{
  int sock;
  struct sockaddr_in addr;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
    {
      perror("socket");
      exit(1);
    }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("connect");
      exit(2);
    }
  /*std::string message = "nameChat";
  unsigned char size_byte = message.size();
  message.insert(message.begin(), size_byte);

  size_t start = 0;
  while (start != message.size())
    {
      int len = send(sock, message.c_str() + start, message.size() - start, 0);
      if (len < 0)
        {
          perror("send failed");
          exit(5);
        }
      start += len;
    }*/
  while (true)
    {
      char buf[100];
      bool first_recv = true;
      unsigned char size = 0;
      std::string msg;
      int bytes_read = recv(sock, buf, 100, 0);
      if(bytes_read > 0)
        {
          //do
           // {
              //if(first_recv)
                //{
                  //size = buf[0];
                  //msg.insert(msg.end(), buf , buf + bytes_read);
                  //first_recv = false;
               // }
              //else
                msg.insert(msg.end(), buf, buf + bytes_read);
           // } while (msg.size() < size);
                 // msg = buf;
                std::string asd = msg;
          std::cout << "message:" << asd;

        }
    }
  close(sock);
  return 0;
}
