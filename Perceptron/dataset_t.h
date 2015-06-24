#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include <map>
#include <utility>

typedef std::pair< std::vector< double >, std::vector<char> >  sample_t;
typedef std::vector< sample_t > samples_t;

struct dataset_t
{
  dataset_t(std::string const &dataset, size_t x_dim, size_t y_dim);
  void split_train_test(double train_portion);
  const samples_t &train_dataset() const;
  samples_t const &test_dataset() const;
  std::pair<size_t, size_t> const & dim() const;

private:
  std::pair<size_t, size_t> dim_;
  samples_t train_samples_;
  samples_t test_samples_;
};
