#include "perceptron.h"
#include <cmath>

perceptron_t::perceptron_t(std::pair<size_t, size_t> dim)
    : dim_(dim)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> range_numb(-1, 1);

    theta_ = range_numb(gen);
    weights_.resize(dim.second);
    for (size_t k = 0; k < dim.second; ++k)
    {
        weights_[k].resize(dim.first);
        std::generate(weights_[k].begin(), weights_[k].end(), [&](){ return range_numb(gen); });
    }
}

perceptron_t::~perceptron_t()
{
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
    std::vector<char> res(dim_.second);
    for (size_t k = 0; k < dim_.second; ++k)
    {
        double prod = std::inner_product(weights_[k].begin(), weights_[k].end(), in_data.begin(), 0.);
        res[k] = prod > theta_ ? 1 : 0;
    }

    return res;
}







