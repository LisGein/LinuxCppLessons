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
#include <cstring>
#include <string>
#include <stdlib.h>


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
  : message("*")
  , end_game(false)
  {

    for (int i = 1; i <= 3; ++i)
       for (int j = 1; j <= 3; ++j)
         {
          pos.x = j;
          pos.y = i;
          pair_pos.insert(std::pair<point_t, char>(pos,'*'));
         }

  }
  ~Plays()
  {}

  void game()
  {
    out_play();
    input_pos();
    forming_check();
  }

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

  bool finish_play()
  {
    return end_game;
  }
private:
  void input_pos()
  {

    std::cout << "Input message" << std::endl;
    std::cin >> message;
    message += ";";
    std::string temp_mess;
    std::cin >> temp_mess;
    message += temp_mess;
    char buf[message.size()];

    temp_mess = message.substr(0, message.find(";"));
    pos.x = atoi (temp_mess.c_str());
    temp_mess = message.substr(message.find(";")+1);
    pos.y = atoi (temp_mess.c_str());

    send(sock, message.c_str(), message.size() + 1, 0);
    recv(sock, buf, sizeof(message), 0);

    std::cout << "\033[2J\033[1;1H";
    if ((pos.x <=3)&&(pos.y<=3))
      {
        pair_pos.erase(pos);
        pair_pos.insert(std::pair<point_t, char>(pos,'x'));
      }
    else
      {
        std::cout << "Invalid input. Try again:\n";
        input_pos();
      }
  }

  void out_play()
  {

    int id = 1;
      for (std::map <point_t, char>::iterator iter=pair_pos.begin(); iter!=pair_pos.end(); ++iter)
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

  void forming_check()
  {
    temp_pos_f.y = 1;
    temp_pos_s.y = 2;
    temp_pos_t.y = 3;

    temp_pos_f.x = 1;
    temp_pos_s.x = 2;
    temp_pos_t.x = 3;
    check();

    temp_pos_f.x = 3;
    temp_pos_t.x = 1;
    check();

    temp_pos_f.x = 1;
    temp_pos_s.x = 1;
    check();

    temp_pos_f.x = 2;
    temp_pos_s.x = 2;
    temp_pos_t.x = 2;
    check();

    temp_pos_f.x = 3;
    temp_pos_s.x = 3;
    temp_pos_t.x = 3;
    check();

    temp_pos_f.x = 1;
    temp_pos_s.x = 2;
    temp_pos_t.x = 3;

    temp_pos_f.y = 1;
    temp_pos_s.y = 1;
    temp_pos_t.y = 1;
    check();

    temp_pos_f.y = 2;
    temp_pos_s.y = 2;
    temp_pos_t.y = 2;
    check();

    temp_pos_f.y = 3;
    temp_pos_s.y = 3;
    temp_pos_t.y = 3;
    check();
  }

  void check()
  {
std::map <point_t, char>::iterator iter = pair_pos.find(temp_pos_f);
    if (iter->second == 'x')
      {
        iter = pair_pos.find(temp_pos_s);
        if(iter->second == 'x')
          {
          iter = pair_pos.find(temp_pos_t);
          if(iter->second == 'x')
            end_game = true;
          }
      }
  }

  struct sockaddr_in addr;
  int sock;
  std::map <point_t, char> pair_pos;
  bool end_game;
  point_t pos;
  std::string message;
  point_t temp_pos_f;
  point_t temp_pos_s;
  point_t temp_pos_t;

};

int main()
{
  Plays plays;
  plays.connected();
  while (!plays.finish_play())
  {
    plays.game();
  }
  plays.closing();
  std::cout << "You win!\n";
  return 0;
}
