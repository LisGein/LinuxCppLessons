#pragma once
#include <cstring>
#include <utility>
#include <vector>
#include <iterator>
#include <map>


typedef std::pair<int, int> pair_t;

const int width = 12;
const int height = 12;

struct point_t
{
	point_t();
	point_t(int x, int y);
	bool operator< (point_t const &other) const;
	int x;
	int y;
};

class Games
{
public:
  Games();
  ~Games();

  void set_data(char &sumb, int &sock);
  void send_data(std::string &buf);
  void game();
  bool finish_play();

private:

  void out_play();
  void input_pos();
  void forming_check();

  int sock_;
  std::map <point_t, char> pair_pos_;
  bool end_game_;
  point_t pos_;
  char sumb_x_;
  char sumb_o_;
};
