#include "game.h"
#include <iostream>


Game::Game(IConnection *connection)
  :end_game_(false)
  , connection_(connection)
{
  if(connection_->first_turn())//установка символа игрока
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

  for (int i = 1; i <= WIDTH; ++i)//заполнения поля для игры
    for (int j = 1; j <= HEIGHT; ++j)
      {
        pos_.x = j;
        pos_.y = i;
        pair_pos_.insert(std::pair<point_t, char>(pos_,'*'));
      }

  directions.push_back(point_t(1, 0));//по х
  directions.push_back(point_t(-1, 0));

  directions.push_back(point_t(1, 1));//диагональ с лева на право
  directions.push_back(point_t(-1, -1));

  directions.push_back(point_t(-1, 1));//диагональ с право на лево
  directions.push_back(point_t(1, -1));

  directions.push_back(point_t(0, 1));//по у
  directions.push_back(point_t(0, -1));
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
      pos_ = (connection_->recv_step());
      send_data(pos_);
      second_player_ = false;
    }
  std::cout << "\033[2J\033[1;1H";
  pos_.x = WIDTH + 1;
  pos_.y = HEIGHT + 1;
  input_pos();
  forming_check();
  connection_->send_step(pos_);
  if (!end_game_)
    {
      pos_ = connection_->recv_step();
      send_data(pos_);
      forming_check();
    }
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
  point_t find_prev_pos = pos_;
  int sign = 0;
  int numb_char = 1;
  for (point_t const &direction : directions)
    {
      find_prev_pos.x = pos_.x + direction.x;
      find_prev_pos.y = pos_.y + direction.y;
      while((find_prev_pos.x <= WIDTH)||(find_prev_pos.y <= HEIGHT)||(find_prev_pos.x >= 0)||(find_prev_pos.y >= 0))
        {
          sign++;
          auto it =  pair_pos_.find(pos_);
          auto iter = pair_pos_.find(find_prev_pos);
          if (iter->second == it->second)
            {
              numb_char++;
              find_prev_pos.x += direction.x;
              find_prev_pos.y += direction.y;
            }
          else
            {
              if (numb_char >=4)
                end_game_ = true;
              if (sign % 2 == 0)
                numb_char = 1;
              break;
            }
        }
    }
}

