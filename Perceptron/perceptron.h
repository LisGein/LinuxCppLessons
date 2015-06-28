#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

typedef std::vector<std::vector<double>> weights_t;

class perceptron_t
{
public:
    perceptron_t(std::pair<size_t, size_t> dim);
    ~perceptron_t();
    bool learn(std::pair< std::vector< double >, std::vector<char> > const &sample);
    std::vector<char> classify(const std::vector<double> &in_data);
    weights_t get_weights();
    void create_weight();
    void load_weight(weights_t const& weights);


private:
    double theta_;
    weights_t weights_;
    std::pair<size_t, size_t> dim_;
    const double learning_rate_ = 0.1;
};


