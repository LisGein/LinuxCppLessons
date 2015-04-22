#pragma once

struct Point_t
{
	Point_t();
	Point_t(int x, int y);
	bool operator< (Point_t const &other) const;
	int x;
	int y;
};

