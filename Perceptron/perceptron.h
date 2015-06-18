#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>

typedef std::vector<std::pair<int, std::vector<double>>> data_pix;

typedef std::vector<double> data_array;

class Perceptron
{
public:
  Perceptron();
  void data_sharing();
  void fill_database();
  void base_read();
  void learning();
  void add_other();
  void start_learning();

private:
  const int SIZE_IMG = 256;
  data_pix weight_;
  data_pix in_pix_;
};


