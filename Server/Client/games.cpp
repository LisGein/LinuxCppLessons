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
  {
    for (int i = 1; i <= WIDTH; ++i)
      for (int j = 1; j <= HEIGHT; ++j)
      {
        pos_.x = j;
        pos_.y = i;
        pair_pos_.insert(std::pair<point_t, char>(pos_,'*'));
      }
  }

Games::~Games(){}



  void  Games::set_symb(char &symb)
  {
    my_symb_ = symb;
    if (my_symb_ == 'x')
      oponent_symb_ = 'o';
    else
      oponent_symb_ = 'x';
    end_game_ = false;
  }

  void  Games::send_data(std::string &buf)
  {
    std::string temp_mess;
    temp_mess = buf.substr(0, buf.find(";"));
    pos_.x = atoi (temp_mess.c_str());
    temp_mess = buf.substr(buf.find(";")+1);
    pos_.y = atoi (temp_mess.c_str());
    pair_pos_.erase(pos_);
    pair_pos_.insert(std::pair<point_t, char>(pos_, oponent_symb_));
  }

  std::string  Games::make_step()
  {
    std::cout << "\033[2J\033[1;1H";
    pos_.x = WIDTH + 1;
    pos_.y = HEIGHT + 1;
    out_play();
    input_pos_ = input_pos();
    forming_check();
    return input_pos_;
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
      if(id != WIDTH)
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

  std::string Games::input_pos()
  {
    std::string message;
    while ((pos_.x > WIDTH)||(pos_.y > HEIGHT))
    {
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
      std::cout << "\033[2J\033[1;1H";
      if ((pos_.x > WIDTH)||(pos_.y > HEIGHT))
        std::cout << "Invalid input. Try again:\n";
    }
        pair_pos_.erase(pos_);
        pair_pos_.insert(std::pair<point_t, char>(pos_, my_symb_));
        out_play();
        return message;
  }

  void  Games::forming_check()
  {
    point_t temp_pos;
    //проверка по горизонтали
    int numb_char = 1;
    temp_pos.y = pos_.y;
    temp_pos.x = pos_.x+1;

    while(temp_pos.x < WIDTH)
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
    while(temp_pos.y < HEIGHT)
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
    while ((temp_pos.x < WIDTH)&&(temp_pos.y < HEIGHT))
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
    while ((temp_pos.x < WIDTH)&&(temp_pos.y > 0))
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
    while ((temp_pos.x > 0)&&(temp_pos.y < HEIGHT))
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

