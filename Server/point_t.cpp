#include "point_t.h"

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
