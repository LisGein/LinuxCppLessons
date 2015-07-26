#pragma once
#include "point_t.h"
#include <cmath>

struct Matrix
{
  Matrix();
  point_3i transform(float x, float y, float z);

private:
  int matrix_[4][4];
  const int C_;
  int size_matrix_;
};

