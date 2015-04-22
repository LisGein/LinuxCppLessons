#include "game.h"
#include <iostream>


Game::Game(IConnection *connection)
  :end_game_(false)
  , connection_(connection)
{
  if(connection_->first_step())
    {
    player_symb_ = 'x';
    op_symb_ = 'o';
    second_player_ = false;
    }
  else
    {
      player_symb_ = 'o';
      op_symb_ = 'x';
      second_player_ = true;
    }
  for (int i = 1; i <= WIDTH; ++i)
    for (int j = 1; j <= HEIGHT; ++j)
    {
      pos_.x = j;
      pos_.y = i;
      pair_pos_.insert(std::pair<point_t, char>(pos_,'*'));
    }
}
Game::~Game(){}
bool Game::finish()
{
  return end_game_;
}
void Game::make_step()
{
  if (second_player_ == true)
    {
      pos_ = (connection_->revc_step());
      send_data(pos_);
      second_player_ = false;
    }
  std::cout << "\033[2J\033[1;1H";
  pos_.x = WIDTH + 1;
  pos_.y = HEIGHT + 1;
  input_pos();
  forming_check();
  connection_->send_step(input_pos_);

  pos_ = connection_->revc_step();
  send_data(pos_);
  forming_check();

}
void Game::show_result()
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
void Game::send_data(point_t &pos_)
{
  pair_pos_.erase(pos_);
  pair_pos_.insert(std::pair<point_t, char>(pos_, op_symb_));
}

void Game::input_pos()
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
      pair_pos_.insert(std::pair<point_t, char>(pos_, player_symb_));
      show_result();

}

void  Game::forming_check()
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
      show_result();
      std::cout << "End";
    }
}

