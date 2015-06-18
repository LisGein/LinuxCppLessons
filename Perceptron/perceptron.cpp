#include "perceptron.h"

Perceptron::Perceptron()
{
}

void Perceptron::data_sharing()
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

      if (to_numb%3 == 0)
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


void Perceptron::fill_database()
{
  data_pix fill_data;
  data_array line;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> range_numb(-1.0, 1.0);
  for(int numb = 0 ; numb < 10; ++numb)
    {
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

void Perceptron::base_read()
{
  std::ifstream read;
  read.open("data.txt", std::ios::in);
  double line;
  int id = 0;
  data_array data_numb;
  while (read >> line)
    {
      if (id == SIZE_IMG)
        {
          std::pair <int, data_array> pair_res;
          pair_res = std::make_pair(line, data_numb);
          weight_.push_back(pair_res);
          id = 0;
          data_numb.clear();
        }
      else
        {
          data_numb.push_back(line);
          id++;
        }
    }
  read.close();
}

void Perceptron::learning()
{
  std::ifstream read_in;
  read_in.open("learning.txt", std::ios::in);
  data_array data_numb;
  double line;
  int id = 0;
  while ( read_in >> line)
    {
      if (id == SIZE_IMG)
        {
          std::pair <int, data_array> pair_res;
          pair_res = std::make_pair(line, data_numb);
          in_pix_.push_back(pair_res);
          id = 0;
          data_numb.clear();
        }
      else
        {
          data_numb.push_back(line);
          id++;
        }
    }
  read_in.close();
}

void Perceptron::add_other()
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

void Perceptron::start_learning()
{
  for (size_t size_in_data; size_in_data < in_pix_.size(); ++size_in_data)
    {
      int numb = in_pix_[size_in_data].first;
      double res;
      int theta = 1;
      for (size_t i = 0; i < weight_.size(); ++i)
        res += in_pix_[size_in_data].second[i]*weight_[numb].second[i] - theta;
      double weight_data;
      for (size_t i = 0; i < weight_[numb].second.size(); ++i)
        weight_data += weight_[numb].second[i];
      if (res > weight_data)
        for (size_t i = 0; i < weight_[numb].second.size(); ++i)
          weight_[numb].second[i] -= in_pix_[size_in_data].second[i];
      else if (res < weight_data)
        for (size_t i = 0; i < weight_[numb].second.size(); ++i)
          weight_[numb].second[i] += in_pix_[size_in_data].second[i];
    }

}
