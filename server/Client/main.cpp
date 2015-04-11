#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdio>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <vector>
#include <map>
#include <iterator>

typedef std::pair<int, int> pair_t;

struct point_t
{
	point_t()
		:x(0), y(0)
	{}
	point_t(int x, int y)
		:x(x), y(y)
	{}
	bool operator< (point_t const &other) const
	{
		if (y < other.y)
			return true;
		if (y == other.y && x < other.x)
			return true;
		return false;
	}
	int x;
	int y;
};

class Plays
{
public:
  Plays()

  {
    char message[] = "*";
    for (int i = 0; i < 3; ++i)
       for (int j = 0; j < 3; ++j)
         {
         pos.x = i;
         pos.y = j;
         pair_pos.insert(std::pair<point_t, char>(pos,'*'));
         }

  }
  ~Plays()
  {}

  void closing()
  {
    close(sock);
  }

  void connected()
  {
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
      perror("socket");
      exit(1);
    }

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror ("connect");
      exit(2);
    }
  }

  void input_pos()
  {

    std::cout << "Input message" << std::endl;
    std::cin >> message;
    char buf[sizeof(message)];
    pos.x = (int)message;
    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);
    printf(buf);

    std::cout << "\nInput message" << std::endl;
    std::cin >> message;
    buf[sizeof(message)];
    pos.y = (int)message;
    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);
    printf(buf);
    pair_pos.insert(std::pair<point_t, char>(pos,'x'));

    std::cout << "\033[2J\033[1;1H";
  }

  void out_play()
  {

    int id = 1;
      for (iter=pair_pos.begin(); iter!=pair_pos.end(); ++iter)
        {
          if(id%3!= 0)
            {
             std::cout << iter->second;
             id++;
            }
          else
            {
              std::cout << iter->second << '\n';
              id++;
            }
        }
  }
private:
  struct sockaddr_in addr;
  int sock;
  std::map <point_t, char> pair_pos;
  std::map <point_t, char>::iterator iter;
  point_t pos;
  char message[];

};

int main()
{
  Plays plays;
  plays.connected();
  plays.out_play();
  while (true)
  {
    plays.input_pos();
    plays.out_play();
  }
  plays.closing();
  return 0;
}

