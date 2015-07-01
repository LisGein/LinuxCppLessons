#pragma once
#include "baseconnection.h"
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
    Game(BaseConnection *iconnection);
    ~Game();
    bool finish();
    void make_step();
private:
    void put_symbol_on_field(const point_t &pos, char symb);
    void make_oponent_step();
    void make_my_step();
    void draw_field();
    point_t read_pos();
    void check_win_combination(const point_t &pos);
private:
    const int WIDTH = 12;
    const int HEIGHT = 12;
    std::vector<point_t> directions;
private:
    bool end_game_;
    BaseConnection *connection_;
    bool first_player_;
    bool player_step_;
    std::map <point_t, char> pair_pos_;
};


