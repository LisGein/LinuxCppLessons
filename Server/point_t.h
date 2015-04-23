#pragma once

struct point_t
{
	point_t();
	point_t(int x, int y);
	bool operator< (point_t const &other) const;
	int x;
	int y;
};

