#include "point_t.h"

template <> template <> point_2<int>::point_2<>(const point_2<float> &v)
    : x(int(v.x+.5))
    , y(int(v.y+.5))
{}

template <> template <> point_2<float>::point_2<>(const point_2<int> &v)
    : x(v.x)
    , y(v.y)
{}

template <> template <> point_3<int>::point_3<>(const point_3<float> &v)
    : x(int(v.x+.5))
    , y(int(v.y+.5))
    , z(int(v.z+.5))
{}

template <> template <> point_3<float>::point_3<>(const point_3<int> &v)
    : x(v.x)
    , y(v.y)
    , z(v.z)
{}
