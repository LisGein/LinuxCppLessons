#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

typedef std::vector<std::pair<int, std::vector<int>>> database;

const int SIZE_IMG = 256;

int max_compare(std::vector<int> &in_data, std::vector<int> &dbase)
{
  int max_agree=0;
  for(size_t db_s = 0; db_s < in_data.size(); ++db_s)
      if (in_data[db_s] == dbase[db_s])
        max_agree++;

  return max_agree;
}

database base_read()
{
  std::ifstream read;
  read.open("def.txt", std::ios::in);
  std::string line;
  int id = 0;
  database results;
  std::vector<int> data_numb;
  while (read >> line)
    {
      std::string asd = line;
      int num = atoi(asd.c_str());
      if (data_numb.size() < SIZE_IMG)
        data_numb.push_back(num);
      else
        {
          if (id != 9)
            {
              if (num == 1)
                {
                  std::pair <int, std::vector<int>> pair_res;
                  pair_res = std::make_pair(id, data_numb);
                  results.push_back(pair_res);
                }
              id++;
            }
          else
            {
              id=0;
              data_numb.clear();
            }
        }
    }
  read.close();
  return results;
}

std::vector<int> in_data()
{
  std::ifstream read_in;
  read_in.open("in.txt", std::ios::in);
  std::vector<int> in;
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

void add_other(std::vector<int> &in_numb, int numb)
{
  std::ofstream read_in;
  read_in.open("def.txt", std::ios::app);
  for (size_t num_vector =0; num_vector < in_numb.size(); ++num_vector)
    read_in << in_numb[num_vector] << ".0000 ";
  for (int to_numb = 0; to_numb < numb; ++to_numb)
    read_in << 0 << " ";
  read_in << 1 << " ";
  for (size_t after_numb = numb ; after_numb < 9; ++after_numb)
    read_in << 0<< " ";
  read_in << "\n";
  read_in.close();
}

int main()
{
  database results = base_read();
  std::vector<int> in_numb = in_data();
  std::pair<int,int> pair_max = std::make_pair(0, 0);
  for(size_t i = 0; i < results.size(); ++i)
    {
      int best_result = max_compare(in_numb, results[i].second);
      if (pair_max.second < best_result)
        pair_max = std::make_pair(results[i].first, best_result);
    }
  std::cout <<  "Youre number: " << pair_max.first << "\n" << "Number of coincidences:" << pair_max.second << "\n";
  if (SIZE_IMG > pair_max.second)
    add_other(in_numb, pair_max.first);
  return 0;
}
