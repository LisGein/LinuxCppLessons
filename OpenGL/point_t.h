#pragma once
#include <cmath>
#include <QtGlobal>


template <typename T>
struct point_2
{
    struct {T x, y;};
    point_2()
        : x(0)
        , y(0)
    {}
    point_2(T x_, T y_)
        : x(x_)
        , y(y_)
    {}
    template <class U> point_2<T>(const point_2<U> &v);
    inline point_2<T> operator +(const point_2<T> &V) const
    {
        return point_2<T>(x+V.x, y+V.y);
    }

    inline point_2<T> operator -(const point_2<T> &V) const
    {
        return point_2<T>(x-V.x, y-V.y);
    }

    inline point_2<T> operator *(float f) const
    {
        return point_2<T>(x*f, y*f);
    }
};

typedef point_2<float> point_2f;
typedef point_2<int>   point_2i;

template <typename T>
struct point_3
{
    struct {T x, y, z;};
    point_3()
        : x(0)
        , y(0)
        , z(0)
    {}
    point_3(T x_, T y_, T z_)
        : x(x_)
        , y(y_)
        , z(z_)
    {}
    template <class U> point_3<T>(const point_3<U> &v);

    inline point_3<T> operator ^(const point_3<T> &v) const
    {
        return point_3<T>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
    }
    inline point_3<T> operator +(const point_3<T> &v) const
    {
        return point_3<T>(x+v.x, y+v.y, z+v.z);
    }
    inline point_3<float> operator -(const point_3<T> &v) const
    {
        return point_3<float>(x-v.x, y-v.y, z-v.z);
    }
    inline point_3<T> operator -(const int v) const
    {
        return point_3<T>(x-v, y-v, z-v);
    }
    inline point_3<T> operator --(int)
    {
        x--;
        y--;
        z--;
        return *this;
    }
    inline point_3<T> operator ++(int)
    {
        x++;
        y++;
        z++;
        return *this;
    }
    inline point_3<T> operator *(float f) const
    {
        return point_3<T>(x*f, y*f, z*f);
    }
    inline T operator *(const point_3<T> &v) const
    {
        return x*v.x + y*v.y + z*v.z;
    }
    float norm () const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    point_3<T> normalize()
    {
        float n = norm();
        x /= n;
        y /= n;
        z /= n;
        return *this;
    }
    T operator[](int i)
    {
        Q_ASSERT((i>=0) && (i<3));
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else
            return z;
    }
};

typedef point_3<float> point_3f;
typedef point_3<int>   point_3i;

template <>template <> point_2<int>::point_2(const point_2<float> &v);
template <>template <> point_2<float>::point_2(const point_2<int> &v);
template <>template <> point_3<int>::point_3(const point_3<float> &v);
template <>template <> point_3<float>::point_3(const point_3<int> &v);

