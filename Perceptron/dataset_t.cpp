#include "dataset_t.h"


dataset_t::dataset_t(std::string const& dataset, size_t x_dim, size_t y_dim)
  : dim_(std::make_pair(x_dim, y_dim))
{
  std::ifstream fin(dataset);
  size_t samples_count;
  fin >> samples_count;//допишем в начало файла вывод wc -l <filename>.txt
  train_samples_.reserve(samples_count);
  for (size_t i = 0; i < samples_count; ++i)
    {
      sample_t sample;
      for (size_t j = 0; j < x_dim; ++j)
        {
          double pix;
          fin >> pix;
          sample.first.push_back(pix);
        }

      for (size_t j = 0; j < y_dim; ++j)
        {
          int hit;
          fin >> hit;
          sample.second.push_back(hit);
        }
      train_samples_.push_back(sample);
    }
}

void dataset_t::split_train_test(double train_portion)
{
  std::random_shuffle(train_samples_.begin(), train_samples_.end());
  size_t pivot = floor(train_samples_.size() * train_portion);
  auto train_end = train_samples_.begin() + pivot + 1;
  std::copy(train_end, train_samples_.end(), std::back_inserter(test_samples_));
  train_samples_.erase(train_end, train_samples_.end());
}

samples_t const &dataset_t::train_dataset() const
{
  return train_samples_;
}

const samples_t &dataset_t::test_dataset() const
{
  return test_samples_;
}

std::pair<size_t, size_t> const & dataset_t::dim() const
{
  return dim_;
}

void dataset_t::save(weights_t const& weights)
{
  std::ofstream read_in;
  read_in.open("data.txt", std::ios::out);
  for (size_t to_numb = 0; to_numb < weights.size(); ++to_numb)
    {
      for (size_t numb = 0; numb < weights[to_numb].size(); ++numb)
        read_in << weights[to_numb][numb] << " ";
      read_in << "\n";
    }
  read_in.close();
}

weights_t dataset_t::load(std::string const& dataset)
{
    std::ifstream read;
    read.open(dataset, std::ios::in);
    weights_t  data;
    std::vector<double> id_data;
    size_t id = 1;
    double read_number;
    while (read >> read_number)
      {
        if (id == dim_.first)
          {
            id_data.push_back(read_number);
            data.push_back(id_data);
            id_data.clear();
            id = 1;
          }

        else
          {
            id_data.push_back(read_number);
            id++;
          }
      }
    read.close();
    return data;
}








