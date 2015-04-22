#include "point_t.h"

Point_t::Point_t()
		:x(0), y(0)
	{}
Point_t::Point_t(int x, int y)
		:x(x), y(y)
	{}
bool Point_t::operator< (Point_t const &other) const
	{
		if (y < other.y)
			return true;
		if (y == other.y && x < other.x)
			return true;
		return false;
	}
