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
    }  while (nickName.size() > 12);

  std::string msg = nickName;
  unsigned char size_byte = msg.size();
  msg.insert(msg.begin(), size_byte);

  size_t start = 0;
  while (start != msg.size())
    {
      int len = send(sock, msg.c_str() + start, msg.size() - start, 0);
      if (len < 0)
        {
          perror("send failed");
          exit(5);
        }

      start += len;
    }
  std::string message;
  while (true)
    {
      std::cout <<"Input message:\n";
      std::cin >> message;
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
        }
    }
  close(sock);
  return 0;
}
