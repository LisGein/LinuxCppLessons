#include "perceptron.h"
#include <cmath>

Perceptron::Perceptron()
{
}

Perceptron::~Perceptron()
{
}

void Perceptron::create_weight()
{
  data_split();
  fill_dataset();
}

int Perceptron::learning(std::string const& dataset_weight, std::string const& dataset_learning)
{
  weight_= read_dataset(dataset_weight);
  in_pix_ = read_dataset(dataset_learning);
  int correct = 0;
  for (size_t numb_in_data = 0; numb_in_data < in_pix_.size(); ++numb_in_data)
    {
      if (find_correct(numb_in_data))
        correct ++;
      add_weight( in_pix_[numb_in_data].first, in_pix_[numb_in_data].second);
      write_data();
    }
  return correct;
}

int Perceptron::test(std::string const& dataset_weight, std::string const& dataset_test)
{
  weight_= read_dataset(dataset_weight);
  in_pix_ = read_dataset(dataset_test);
  int correct = 0;
  for (size_t numb_in_data = 0; numb_in_data < in_pix_.size(); ++numb_in_data)
    if (find_correct(numb_in_data))
      correct ++;
  return correct;
}

bool Perceptron::find_correct(int numb)
{
  std::pair<int, double> max_pair;
  max_pair = std::make_pair(0, 0);
  double max = 0;
  for (size_t id = 0; id < weight_.size(); ++id)
    {
      for (size_t i = 0; i <  SIZE_IMG; ++i)
        {
          max += weight_[id].second[i] * in_pix_[id].second[i];
        }
      if(max_pair.second > max)
        max_pair = std::make_pair(id, max);
    }
  if (max_pair.first == numb)
    return true;
  else
    return false;
}

int Perceptron::size_in_data()
{
  return in_pix_.size();
}

void Perceptron::data_split()
{
  std::ifstream read;
  read.open("dat.txt", std::ios::in);
  double line;
  int id = 0;
  int numb = 0;
  int v_numb = 0;
  data_array data_numbers;
  while (read >> line)
    {
      if (id >= SIZE_IMG)
        {
          v_numb++;
          if (line!=0)
            {
              std::pair <int, data_array> pair_res;
              pair_res = std::make_pair(numb, data_numbers);
              weight_.push_back(pair_res);
            }
          else
            numb++;

          if (v_numb == 10)
            {
              id = 0;
              data_numbers.clear();
              numb = 0;
              v_numb = 0;
            }
        }
      else
        {
          data_numbers.push_back(line);
          id++;
        }
    }
  read.close();

  std::ofstream learn_data;
  learn_data.open("learning.txt", std::ios::out);
  std::ofstream test_data;
  test_data.open("test.txt", std::ios::out);
  std::random_shuffle ( weight_.begin(), weight_.end() );
  for (size_t to_numb = 0; to_numb < weight_.size(); ++to_numb)
    {
      if (to_numb%5 == 0)
        {
          for (size_t idx =0; idx < SIZE_IMG; ++idx)
            test_data << weight_[to_numb].second[idx] << " ";
          test_data << " " << weight_[to_numb].first << " ";
          test_data << "\n";
        }
      else
        {
          for (size_t idx =0; idx < SIZE_IMG; ++idx)
            learn_data << weight_[to_numb].second[idx] << " ";
          learn_data << " " << weight_[to_numb].first << " ";
          learn_data << "\n";
        }
    }
  learn_data.close();
  test_data.close();
}

void Perceptron::fill_dataset()
{
  sample_t fill_data;
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
      fill_data.push_back(pair_res);
      line.clear();
    }
  std::ofstream weight;
  weight.open("data.txt", std::ios::out);
  for (size_t to_numb = 0; to_numb < fill_data.size(); ++to_numb)
    {
      for (size_t idx =0; idx < SIZE_IMG; ++idx)
        weight << fill_data[to_numb].second[idx] << " ";
      weight << " " << fill_data[to_numb].first << " ";
      weight << "\n";
    }
  weight.close();
}

sample_t Perceptron::read_dataset(std::string const& dataset)
{
  std::ifstream read;
  read.open(dataset, std::ios::in);
  sample_t data;
  data_array data_numb;
  double read_number;
  int id = 0;
  while (read >> read_number)
    {
      if (id == SIZE_IMG)
        {
          std::pair <int, data_array> pair_res = std::make_pair(read_number, data_numb);
          data.push_back(pair_res);
          id = 0;
          data_numb.clear();
        }
      else
        {
          data_numb.push_back(read_number);
          id++;
        }
    }
  read.close();
  return data;
}

double Perceptron::size_weight(int numb)
{
  double weight_data = 0;
  for (size_t i = 0; i < weight_[numb].second.size(); ++i)
    weight_data += weight_[numb].second[i];
  return weight_data;
}

double Perceptron::size_change_data(int numb, data_array in_binary)
{
  double res = 0;
  int theta = 0.0001;
  for (size_t i = 0; i < weight_[numb].second.size(); ++i)
    res += in_binary[i]*weight_[numb].second[i] - theta;
  return res;
}

void Perceptron::write_data()
{
  std::ofstream read_in;
  read_in.open("data.txt", std::ios::out);
  for (size_t to_numb = 0; to_numb < weight_.size(); ++to_numb)
    {
      for (size_t idx =0; idx < SIZE_IMG; ++idx)
        read_in << weight_[to_numb].second[idx] << " ";
      read_in << " " << weight_[to_numb].first << " ";
      read_in << "\n";
    }
  read_in.close();
}

void Perceptron::add_weight(int numb, data_array in_binary)
{
  double res = size_change_data( numb, in_binary);
  double weight_data = size_weight(numb);
  data_array temp_mass;
  for (size_t i = 0; i < weight_[numb].second.size(); ++i)
    if (res < weight_data)
      temp_mass.push_back(weight_[numb].second[i] + in_binary[i]);
    else if (weight_data > res)
      temp_mass.push_back(weight_[numb].second[i] - in_binary[i]);
  weight_[numb].second = temp_mass;
}
