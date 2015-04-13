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

const int width = 12;
const int height = 12;

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
  , player_f("x")
  , player_s("o")
  {

    for (int i = 1; i <= width; ++i)
       for (int j = 1; j <= height; ++j)
         {
          pos.x = j;
          pos.y = i;
          pair_pos.insert(std::pair<point_t, char>(pos,'*'));
         }

  }
  ~Plays()
  {}

  void set_data()
  {
    std::cout << "Input port second player\n";
    std::cin >> listport;

    std::cout << "x or o?\n";
    char colibrate_step;
    std::cin >> colibrate_step;

    connected();
  }

  void game()
  {
    out_play();
    input_pos();
    forming_check();
  }

  void closing()
  {
    out_play();
    close(sock);
  }

  void connected()
  {
    addr.sin_family = AF_INET;
    addr.sin_port = htons(listport);
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

    temp_mess = message.substr(0, message.find(";"));
    pos.x = atoi (temp_mess.c_str());
    temp_mess = message.substr(message.find(";")+1);
    pos.y = atoi (temp_mess.c_str());

    if ((pos.x <=width)&&(pos.y<=height))
      {
        char buf[message.size()];
        send(sock, message.c_str(), message.size() + 1, 0);
        //recv(sock, buf, sizeof(message), 0);
        std::cout << buf;

        std::cout << "\033[2J\033[1;1H";
        pair_pos.erase(pos);
        pair_pos.insert(std::pair<point_t, char>(pos,'x'));
      }
    else
      {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Invalid input. Try again:\n";
        input_pos();
      }
  }

  void listen_other()
  {

  }

  void out_play()
  {

    int id = 1;
      for (auto iter=pair_pos.begin(); iter!=pair_pos.end(); ++iter)
        {
          if(id != width)
            {
             std::cout << iter->second << " ";
             id++;
            }
          else
            {
              std::cout << iter->second << " " << '\n';
              id=1;
            }
        }
  }

  void forming_check()
  {
    //проверка по горизонтали
    int numb_char = 1;
    temp_pos.y = pos.y;
    temp_pos.x = pos.x+1;

    while(temp_pos.x < width)
    {
      auto it =  pair_pos.find(pos);
      auto iter = pair_pos.find(temp_pos);
           if (iter->second == it->second)
             {
              numb_char++;
              temp_pos.x++;
             }
           else
             {
              break;
             }
    }
    temp_pos.x = pos.x-1;
    while(temp_pos.x > 0)
    {

      auto it = pair_pos.find(pos);
      auto iter = pair_pos.find(temp_pos);
           if (iter->second == it->second)
             {
              numb_char++;
              temp_pos.x--;
             }
           else
             {
              break;
             }
    }
    if (numb_char >=4)
       end_game = true;

    //проверка по вертикали
      numb_char = 1;
      temp_pos.y = pos.y+1;
      temp_pos.x = pos.x;
      while(temp_pos.y < height)
      {
        auto it = pair_pos.find(pos);
        auto iter = pair_pos.find(temp_pos);
             if (iter->second == it->second)
               {
                  numb_char++;
                  temp_pos.y++;
               }
             else
               {
                break;
               }
      }
       temp_pos.y = pos.y-1;
       while(temp_pos.y > 0)
       {
         auto it = pair_pos.find(pos);
         auto iter = pair_pos.find(temp_pos);
              if (iter->second == it->second)
                {
                   numb_char++;
                   temp_pos.y--;
                }
              else
                {
                 break;
                }
       }
      if (numb_char >=4)
         end_game = true;

 //проверка по вертикали вниз
      numb_char = 1;
      temp_pos.x = pos.x+1;
      temp_pos.y = pos.y+1;
      while ((temp_pos.x < width)&&(temp_pos.y < height))
      {
        auto it = pair_pos.find(pos);
        auto iter = pair_pos.find(temp_pos);
             if (iter->second == it->second)
               {
                numb_char++;
                temp_pos.x++;
                temp_pos.y++;
               }
             else
             {
              break;
             }
      }
      temp_pos.x = pos.x-1;
      temp_pos.y = pos.y-1;
      while ((temp_pos.x > 0)&&(temp_pos.y > 0))
      {
        auto it = pair_pos.find(pos);
        auto iter = pair_pos.find(temp_pos);
             if (iter->second == it->second)
               {
                numb_char++;
                temp_pos.x--;
                temp_pos.y--;
               }
             else
               {
                break;
               }
      }
      if (numb_char >=4)
         end_game = true;

      //проверка по вертикали вверх
           numb_char = 1;
           temp_pos.x = pos.x+1;
           temp_pos.y = pos.y-1;
           while ((temp_pos.x < width)&&(temp_pos.y > 0))
           {
             auto it = pair_pos.find(pos);
             auto iter = pair_pos.find(temp_pos);
                  if (iter->second == it->second)
                    {
                     numb_char++;
                     temp_pos.x++;
                     temp_pos.y--;
                    }
                  else
                    {
                     break;
                    }
           }
           temp_pos.x = pos.x-1;
           temp_pos.y = pos.y+1;
           while ((temp_pos.x > 0)&&(temp_pos.y < height))
           {
             auto it = pair_pos.find(pos);
             auto iter = pair_pos.find(temp_pos);
                  if (iter->second == it->second)
                    {
                     numb_char++;
                     temp_pos.x--;
                     temp_pos.y++;
                    }
                  else
                    {
                     break;
                    }
           }
           if (numb_char >=4)
              end_game = true;

  }

  int port;
  int listport;
  struct sockaddr_in addr;
  int sock, sock_lis;
  std::map <point_t, char> pair_pos;
  std::map <int, char> users;
  bool end_game;
  point_t pos;
  std::string message;
  std::string player_f;
  std::string player_s;
  point_t temp_pos;

};

int main()
{
  int port;
  std::cout << "Input your port\n";
  std::cin >> port;
Plays plays;

  int sock, listener;
  struct sockaddr_in addr;
  char buf[1024];
  int bytes_read;
  listener = socket(AF_INET, SOCK_STREAM, 0);
  if (listener < 0)
    {
      perror("socket");
      exit(1);
    }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(listener, (struct sockaddr *)&addr, sizeof(addr))<0)
    {
      perror("bind");
      exit(2);
    }
  listen(listener, 2);
  while(1)
    {

      plays.set_data();
      while (!plays.finish_play())
      {
        plays.game();

      sock = accept(listener, NULL, NULL);
      if(sock < 0)
        {
          perror("accept");
          exit(3);
        }

      switch (fork())
        {
        case -1:
          perror("fork");
          break;
        case 0:
          close(listener);
          while(1)
            {


              bytes_read = recv(sock, buf, 1024, 0);
              if(bytes_read <= 0)
                break;
              std::cout << buf << std::endl;
              send(sock, buf, bytes_read, 0);

            }

          close(sock);
          _exit(0);

        default:
          {


            close(sock);
          }
        }
      }
    }
  plays.closing();
  close(listener);
  return 0;
}
