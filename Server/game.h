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

private:
  const int WIDTH = 12;
  const int HEIGHT = 12;
  IConnection *connection_;
  bool end_game_;
  bool second_player_;
  char player_symb_;
  char op_symb_;
  std::vector<point_t> directions;
  std::string input_pos_;
  std::map <point_t, char> pair_pos_;
  point_t pos_;

  void show_result();
  void send_data(point_t &pos_);
  void input_pos();
  void forming_check();
};


