#pragma once
#include "point_t.h"
#include <cmath>
#include <QVector>

const int width_ = 640;
const int height_ = 600;
const int depth_ = 200;

struct Matrix
{
  Matrix();
  void identity();
  void view_port(int x, int y, int w, int h);
  QVector<float>& operator[](int i);
  Matrix operator*(Matrix& a);
  point_3f operator*(point_3f a);

private:
  QVector<QVector<float>> matrix_;
  int size_matrix_;
};

Matrix lookat(point_3f eye, point_3f center, point_3f up);
