#include "perceptron.h"
#include <cmath>

Perceptron::Perceptron(std::pair<size_t, size_t> dim)
  :dim_(dim)
{
  data_array line;

  for(int numb = 0 ; numb < 10; ++numb)
    {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<double> range_numb(-1, 1);
      for (size_t i = 0; i < SIZE_IMG; ++i)
        line.push_back(range_numb(gen));

      std::pair <int, data_array> pair_res;
      pair_res = std::make_pair(numb, line);
      weight_.push_back(pair_res);
      line.clear();
    }
}

Perceptron::~Perceptron()
{
}

bool Perceptron::y(double res)
{
  return res >= theta_;
}

bool Perceptron::learn(const std::pair<std::vector<double>, std::vector<char>> &in_data)
{
  double theta = 0.001;
  double learning_rate = 0.01;
  int numb;
  for (int i = 0; i < dim_.second; ++i)
    if (in_data.second[i] != '0')
      numb = i;
  double res = size_change_data( numb, in_data.first);
  if (res > theta)
    {
      for (int idx_data = 0; idx_data < in_data.first.size(); ++idx_data)
        weight_[numb].second[idx_data] += learning_rate * ( y(res) - in_data.first[idx_data] ) * in_data.second[idx_data];

      return false;
    }
  else if (theta < res)
    {
      for (int idx_data = 0; idx_data < in_data.first.size(); ++idx_data)
        weight_[numb].second[idx_data] -= learning_rate * ( y(res) - in_data.first[idx_data] ) * in_data.second[idx_data];

      return false;
    }
  else
    return true;
}

std::vector< char> Perceptron::classify(const std::vector<double> &in_data)
{
  double max_comp = 0;
  int numb_comp = 0;
  for (int i = 0; i < weight_.size(); ++i)
    {
      if (max_comp < size_change_data(i, in_data))
        numb_comp = i;
    }
  std::vector< char> return_numb;
  for (int i = 0; i < dim_.second; ++i)
    if (numb_comp != i)
      return_numb.push_back('0');
    else
      return_numb.push_back('1');
  return return_numb;
}

double Perceptron::size_change_data(int numb, data_array in_binary)
{
  double res = 0;
  for (size_t i = 0; i < weight_[numb].second.size(); ++i)
    res += in_binary[i]*weight_[numb].second[i];
  return res;
}







