#include "games.h"
#include <string>
#include <iostream>
#include <sys/socket.h>

point_t::point_t()
		:x(0), y(0)
	{}
point_t::point_t(int x, int y)
		:x(x), y(y)
	{}
bool point_t::operator< (point_t const &other) const
	{
		if (y < other.y)
			return true;
		if (y == other.y && x < other.x)
			return true;
		return false;
	}

Games::Games()
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

 Games::~Games(){}

  void  Games::set_data(char &sumb, int &sock)
  {
    sumb_x_ = sumb;
    if (sumb_x_ == 'x')
      sumb_o_ = 'o';
    else
      sumb_o_ = 'x';
    sock_=sock;
  }

  void  Games::send_data(std::string &buf)
  {
    std::string temp_mess;
    temp_mess = buf.substr(0, buf.find(";"));
    pos_.x = atoi (temp_mess.c_str());
    temp_mess = buf.substr(buf.find(";")+1);
    pos_.y = atoi (temp_mess.c_str());
    pair_pos_.erase(pos_);
    pair_pos_.insert(std::pair<point_t, char>(pos_, sumb_o_));
  }

  void  Games::game()
  {
    std::cout << "\033[2J\033[1;1H";
    out_play();
    input_pos();
    forming_check();
  }

  bool  Games::finish_play()
  {
    return end_game_;
  }

  void  Games::out_play()
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

  void  Games::input_pos()
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

  void  Games::forming_check()
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

    if (end_game_ == true)
      {
        out_play();
        std::cout << "End";
      }
  }

