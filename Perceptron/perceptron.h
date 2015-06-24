#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

typedef std::vector<std::pair<int, std::vector<double>>> data_weight;

typedef std::vector<double> data_array;

class Perceptron
{
public:
  Perceptron(std::pair<size_t, size_t> dim);
  ~Perceptron();
  bool learn(const std::pair<std::vector<double>, std::vector<char> > &in_data);
  std::vector<char> classify(const std::vector<double> &in_data);


private:
  double theta_ = 0.001;
  const int SIZE_IMG = 256;
  data_weight weight_;
  std::pair<size_t, size_t> dim_;

  double size_change_data(int numb, data_array in_binary);
  bool y(double res);
};


