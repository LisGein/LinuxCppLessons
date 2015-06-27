#pragma once
#include <vector>
#include <algorithm>

class ConfusionMatrix
{
public:
  ConfusionMatrix(size_t dim);
  void incrementacia(std::vector<char> const &numb, std::vector<char> const &find_numb);
  double f_1();
  void clear_confusion_matrix();

private:
  std::vector<std::vector<int>> confusion_matrix_;
  size_t dim_;
};

