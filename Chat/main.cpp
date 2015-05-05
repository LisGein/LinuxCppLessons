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
  while (true)
    {
      char buf[100];
      std::string msg;
      int bytes_read = recv(sock, buf, 100, 0);
      if(bytes_read > 0)
        {
          msg = buf;
          std::cout  << msg << std::endl;
        }
    }
  close(sock);
  return 0;
}
