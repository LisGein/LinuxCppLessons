#include "perceptron.h"
#include <cmath>

perceptron_t::perceptron_t(std::pair<size_t, size_t> dim)
  : dim_(dim)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> range_numb(-1, 1);  
  theta_ = range_numb(gen);
}

perceptron_t::~perceptron_t()
{
}

void perceptron_t::create_weight()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> range_numb(-1, 1);

  weights_.resize(dim_.second);
  for (size_t k = 0; k < dim_.second; ++k)
    {
      weights_[k].resize(dim_.first);
      std::generate(weights_[k].begin(), weights_[k].end(), [&](){ return range_numb(gen); });
    }
}

void perceptron_t::load_weight(weights_t const& weights)
{
  weights_ = weights;
}

bool perceptron_t::learn(const std::pair<std::vector<double>, std::vector<char> > &sample)
{
  auto y = classify(sample.first);
  for (size_t k = 0; k < dim_.second; ++k)
    {
      for (size_t i = 0; i < dim_.first; ++i)
        weights_[k][i] += learning_rate_ * (sample.second[k] - y[k]) * sample.first[i];
      
      theta_ -= learning_rate_ * (sample.second[k] - y[k]);
    }
  
  return y == sample.second;
}

std::vector<char> perceptron_t::classify(const std::vector<double> &in_data)
{
  std::vector<double> res(dim_.second);
  for (size_t k = 0; k < dim_.second; ++k)
    {
      double prod = std::inner_product(weights_[k].begin(), weights_[k].end(), in_data.begin(), 0.);
      res[k] = prod - theta_;
    }
  auto result = std::max_element(res.begin(), res.end());
  size_t idx_max = std::distance(res.begin(), result);
  std::vector<char> binary_numb;
  binary_numb.resize(dim_.second);
  binary_numb[idx_max] = 1;
  return binary_numb;
}

weights_t perceptron_t::get_weights()
{
  return weights_;
}



