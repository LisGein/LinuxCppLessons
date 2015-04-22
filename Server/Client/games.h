#pragma once
#include <cstring>
#include <utility>
#include <vector>
#include <iterator>
#include <map>


typedef std::pair<int, int> pair_t;

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

  void set_sock(int &sock);
  void set_symb(char &symb);
  void set_data(char &sumb, int &sock);
  void send_data(std::string &buf);
  std::string make_step();
  bool finish_play();

private:

  void out_play();
  std::string input_pos();
  void forming_check();
  
  const int WIDTH = 12;
  const int HEIGHT = 12;
  std::string input_pos_;
  std::map <point_t, char> pair_pos_;
  bool end_game_;
  point_t pos_;
  char my_symb_;
  char oponent_symb_;
  point_t temp_pos;
};
