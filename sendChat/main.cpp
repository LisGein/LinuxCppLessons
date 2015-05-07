#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

char buf[5];

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
  std::string nickName;
    do
      {
        std::cout << "Input nick\n"
                  << "Your nickname must be less than 12 characters!\n";
        std::cin >> nickName;
        send(sock, nickName.c_str(), nickName.size(), 0);
      }  while (nickName.size() > 12);
  std::string message;
  std::cout <<"Input message:\n";
  while (true)
    {
      std::getline(std::cin, message);
      send(sock, message.c_str(), message.size()+1, 0);

    }
  close(sock);
  return 0;
}
