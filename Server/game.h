#pragma once
#include "iconnection.h"
#include <cstring>
#include <utility>
#include <vector>
#include <iterator>
#include <map>
#include <memory>
#include "point_t.h"


class Game
{
public:
  Game(IConnection *iconnection);
  ~Game();
  bool finish();
  void make_step();
  void show_result();

private:
  IConnection *connection_;
  Point_t point_t;
  bool end_game_;
  char player_symb_;
  bool second_player_;
  char op_symb_;
  const int WIDTH = 12;
  const int HEIGHT = 12;
  std::string input_pos_;
  std::map <point_t, char> pair_pos_;
  point_t pos_;
  point_t temp_pos;

  void send_data(point_t &pos_);
  void input_pos();
  void forming_check();
};


