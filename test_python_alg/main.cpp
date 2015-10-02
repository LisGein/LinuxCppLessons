#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>


int main()
{
//         std::ifstream data("data1.tsv");
//         std::string str;
//         while ( std::getline(data, str))
//                  std::cout << str << std::endl;

         std::vector< std::vector<std::pair<int, int> > > array;
         std::vector<std::pair<int, int> > s_array = {std::make_pair<int, int>(1, 2),
                                                     std::make_pair<int, int>(2, 3),
                                                     std::make_pair<int, int>(4,8)};
         array.push_back(s_array);
         s_array = {std::make_pair<int, int>(4, 8),
                    std::make_pair<int, int>(6, 3),
                    std::make_pair<int, int>(1, 8)};
         array.push_back(s_array);
         for (int i = 0; i < array.size(); ++i)
                  for (int j = 0; j < array[i].size(); ++j)
                           std::cout << array[i][j].first << ", " << array[i][j].second << std::endl;

         std::vector<std::pair<int, int > > mass;
         for (int i = 0; i < array.size(); ++i)
         {
                  std::pair<int, int> prev_pair(array[i][0].first, array[i][0].second);
                  if (!mass.empty())
                  {
                           if (prev_pair != mass[mass.size()-1])
                                    mass.push_back(prev_pair);
                  }
                  else
                           mass.push_back(prev_pair);
                  for (int j = 1; j < array[i].size(); ++j)
                  {
                           std::pair<int, int> prev_pair(array[i][j].first, array[i][j].second);
                           if (prev_pair != mass[mass.size()-1])
                                 mass.push_back(prev_pair);

                  }
                  std::pair<int, int> next_pair(array[i][array[i].size()-1].first, array[i][array[i].size()-1].second);
                  if (next_pair != mass[mass.size()-1])
                           mass.push_back(next_pair);
         }


         std::vector< std::vector<std::pair<int, int> > > new_array = {mass};



         return 0;
}

