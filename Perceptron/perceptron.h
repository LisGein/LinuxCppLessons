#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

typedef std::vector<std::pair<int, std::vector<double>>> sample_t;

typedef std::vector<double> data_array;

class Perceptron
{
public:
  Perceptron();
  ~Perceptron();
  sample_t read_dataset(std::string const& dataset);
  void create_weight();
  int learning(const std::string &dataset_weight, const std::string &dataset_learning);
  int size_in_data();
  int test(const std::string &dataset_weight, const std::string &dataset_test);

private:
  const int SIZE_IMG = 256;
  sample_t weight_;
  sample_t in_pix_;

  void data_split();
  void fill_dataset();
  double size_weight(int numb);
  double size_change_data(int numb, data_array in_binary);
  void write_data();
  void add_weight(int numb, data_array in_binary);
  bool find_correct(int numb);
};


