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

class Games
{
public:
  Games()
  : end_game_(false)
  {

    for (int i = 1; i <= width; ++i)
      for (int j = 1; j <= height; ++j)
      {
        pos_.x = j;
        pos_.y = i;
        pair_pos_.insert(std::pair<point_t, char>(pos_,'*'));
      }
  }
  ~Games()
  {}

  void set_data(char &sumb)
  {
    sumb_x_ = sumb;
    if (sumb_x_ == 'x')
      sumb_o_ = 'o';
    else
      sumb_o_ = 'x';
    std::cout << "Input port second player\n";
    std::cin >> listen_port_;
    connected();
  }

  void send_data(std::string &bu)
  {
    std::string temp_mess;
    temp_mess = bu.substr(0, bu.find(";"));
    pos_.x = atoi (temp_mess.c_str());
    temp_mess = bu.substr(bu.find(";")+1);
    pos_.y = atoi (temp_mess.c_str());
    pair_pos_.erase(pos_);
    pair_pos_.insert(std::pair<point_t, char>(pos_, sumb_o_));
  }

  void game()
  {
    std::cout << "\033[2J\033[1;1H";
    out_play();
    input_pos();
    forming_check();
  }

  void closing()
  {
    out_play();
    close(sock_);
  }

  bool finish_play()
  {
    return end_game_;
  }

private:
  void connected()
  {
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(listen_port_);
    addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_ < 0)
    {
      perror("socket");
      exit(1);
    }
    if(connect(sock_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
    {
      perror ("connect");
      exit(2);
    }
  }

  void out_play()
  {
    int id = 1;
    for (auto iter=pair_pos_.begin(); iter!=pair_pos_.end(); ++iter)
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

  void input_pos()
  {
    std::string message;
    std::cout << "Input message" << std::endl;
    std::cin >> message;
    message += ";";
    std::string temp_mess;
    std::cin >> temp_mess;
    message += temp_mess;

    temp_mess = message.substr(0, message.find(";"));
    pos_.x = atoi (temp_mess.c_str());
    temp_mess = message.substr(message.find(";")+1);
    pos_.y = atoi (temp_mess.c_str());

    if ((pos_.x <=width)&&(pos_.y<=height))
    {
      send(sock_, message.c_str(), message.size() + 1, 0);
      std::cout << "\033[2J\033[1;1H";
      pair_pos_.erase(pos_);
      pair_pos_.insert(std::pair<point_t, char>(pos_, sumb_x_));
      out_play();
    }
    else
    {
      std::cout << "\033[2J\033[1;1H";
      std::cout << "Invalid input. Try again:\n";
      input_pos();
    }
  }

  void forming_check()
  {
    point_t temp_pos;
    //проверка по горизонтали
    int numb_char = 1;
    temp_pos.y = pos_.y;
    temp_pos.x = pos_.x+1;

    while(temp_pos.x < width)
    {
      auto it =  pair_pos_.find(pos_);
      auto iter = pair_pos_.find(temp_pos);
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
    temp_pos.x = pos_.x-1;
    while(temp_pos.x > 0)
    {

      auto it = pair_pos_.find(pos_);
      auto iter = pair_pos_.find(temp_pos);
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
       end_game_ = true;

    //проверка по вертикали
    numb_char = 1;
    temp_pos.y = pos_.y+1;
    temp_pos.x = pos_.x;
    while(temp_pos.y < height)
    {
      auto it = pair_pos_.find(pos_);
      auto iter = pair_pos_.find(temp_pos);
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
    temp_pos.y = pos_.y-1;
    while(temp_pos.y > 0)
    {
         auto it = pair_pos_.find(pos_);
         auto iter = pair_pos_.find(temp_pos);
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
      end_game_ = true;

 //проверка по вертикали вниз
    numb_char = 1;
    temp_pos.x = pos_.x+1;
    temp_pos.y = pos_.y+1;
    while ((temp_pos.x < width)&&(temp_pos.y < height))
    {
      auto it = pair_pos_.find(pos_);
      auto iter = pair_pos_.find(temp_pos);
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
    temp_pos.x = pos_.x-1;
    temp_pos.y = pos_.y-1;
    while ((temp_pos.x > 0)&&(temp_pos.y > 0))
    {
      auto it = pair_pos_.find(pos_);
      auto iter = pair_pos_.find(temp_pos);
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
       end_game_ = true;

      //проверка по вертикали вверх
    numb_char = 1;
    temp_pos.x = pos_.x+1;
    temp_pos.y = pos_.y-1;
    while ((temp_pos.x < width)&&(temp_pos.y > 0))
    {
      auto it = pair_pos_.find(pos_);
      auto iter = pair_pos_.find(temp_pos);
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
    temp_pos.x = pos_.x-1;
    temp_pos.y = pos_.y+1;
    while ((temp_pos.x > 0)&&(temp_pos.y < height))
    {
      auto it = pair_pos_.find(pos_);
      auto iter = pair_pos_.find(temp_pos);
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
        end_game_ = true;

  }

  int listen_port_;
  struct sockaddr_in addr_;
  int sock_;
  std::map <point_t, char> pair_pos_;
  bool end_game_;
  point_t pos_;
  char sumb_x_;
  char sumb_o_;
};

int main()
{
  int port;
  std::cout << "Input your port\n";
  std::cin >> port;
  Games games;

  int sock, listener;
  struct sockaddr_in addr;
  std::string buf;
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

  std::cout << "x or o?\n";
  char colibrate_sumb;
  std::cin >> colibrate_sumb;
  games.set_data(colibrate_sumb);

  sock = accept(listener, NULL, NULL);
  if(sock < 0)
  {
    perror("accept");
    exit(3);
  }
  while (!games.finish_play())
  {
  if (colibrate_sumb == 'o')
  {
    char mes[buf.size()];
    bytes_read = recv(sock, mes, sizeof(buf), 0);
          if(bytes_read <= 0)
            break;
    send(sock, buf.c_str(), bytes_read, 0);
    std::string sdr = mes;
    games.send_data(sdr);
    std::cout << "\033[2J\033[1;1H";
  }
    games.game();
    char mes[buf.size()];
    bytes_read = recv(sock, mes, sizeof(buf), 0);
    if(bytes_read <= 0)
      break;
    send(sock, buf.c_str(), bytes_read, 0);
    std::string sdr = mes;
    games.send_data(sdr);
  }
  games.closing();
  close(sock);
  close(listener);
  return 0;
}
