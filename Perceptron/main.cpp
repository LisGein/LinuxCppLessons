#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

typedef std::vector<std::pair<int, std::vector<int>>> database;

typedef std::vector<int> data_array;

const int SIZE_IMG = 256;

database base_read()
{
  std::ifstream read;
  read.open("def.txt", std::ios::in);
  std::string line;
  int id = 0;
  database results;
  data_array data_numb;
  while (read >> line)
    {
      std::string asd = line;
      int num = atoi(asd.c_str());
      if (id == SIZE_IMG)
        {
          std::pair <int, data_array> pair_res;
          pair_res = std::make_pair(num, data_numb);
          results.push_back(pair_res);
          id = 0;
          data_numb.clear();
        }
      else
        {
          data_numb.push_back(num);
          id++;
        }
    }
  read.close();
  return results;
}

data_array in_data()
{
  std::ifstream read_in;
  read_in.open("in.txt", std::ios::in);
  data_array in;
  std::string lines;
  int asda;
  while ( read_in >> lines)
    {
      std::string asd = lines;
      asda = atoi(asd.c_str());
      in.push_back(asda);
    }
  read_in.close();
  return in;
}

void add_other(database const &results)
{
  std::ofstream read_in;
  read_in.open("def.txt", std::ios::out);
  for (size_t to_numb = 0; to_numb < results.size(); ++to_numb)
    {
      for (size_t idx =0; idx < SIZE_IMG; ++idx)
        read_in << results[to_numb].second[idx] << " ";
      read_in << " " << results[to_numb].first << " ";
      read_in << "\n";
    }
  read_in.close();
}

data_array start_learning(data_array &std_data, data_array const &in_numb)
{
  double res;
  int theta = 1;
  for (size_t i = 0; i < std_data.size(); ++i)
    res += in_numb[i]*std_data[i] - theta;
  double weight;
  for (size_t i = 0; i < std_data.size(); ++i)
    weight += std_data[i];
  if (res > weight)
    for (size_t i = 0; i < std_data.size(); ++i)
      std_data[i] -= in_numb[i];
  else if (res < weight)
    for (size_t i = 0; i < std_data.size(); ++i)
      std_data[i] += in_numb[i];
  return std_data;
}

int main()
{
  int number_read = 0;
  database results = base_read();
  data_array in_numb = in_data();
  data_array change = start_learning(results[number_read].second, in_numb);
  results[number_read].second = change;
  add_other(results);
  return 0;
}
