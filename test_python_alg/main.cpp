#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>

typedef std::vector<std::pair<double, double> > array_coor;
typedef std::vector<std::vector<std::pair<double, double> > > array;

array break_array(array_coor c_array, double eps)
{
   array new_coor;
   for (int i = c_array.size()-1; i > 0; --i)
   {
      double dist = std::sqrt(std::pow(c_array[i+1].first - c_array[0].first , 2) + std::pow(c_array[i+1].second - c_array[0].second, 2));
      if (dist <= eps)
      {
         array_coor l_array;
         array_coor r_array;
         for (int f = 0; f <= i; ++f)
            l_array.push_back(c_array[f]);

         for (int f = i; f < c_array.size()-1; ++f)
            r_array.push_back(c_array[f]);

         new_coor.push_back(l_array);
         new_coor.push_back(r_array);
         std::cout << dist << " " << i << " break\n";
         break;
      }
   }
   for (int i = c_array.size()-1; i > 0; --i)
   std::cout << std::sqrt(std::pow(c_array[i+1].first - c_array[0].first , 2) + std::pow(c_array[i+1].second - c_array[0].second, 2)) <<"\n";
   std::cout << eps <<" eps\n";
   return new_coor;
}

int main()
{
   std::ifstream data_lat("lat.tsv");
   std::string name;
   char lat [256];
   data_lat >> name;
   std::vector<double>  lat_coor;
   while (data_lat >> lat)
      lat_coor.push_back(std::atof(lat));
   data_lat.close();


   std::ifstream data_lon("lat.tsv");
   char lon [256];
   data_lon >> name;
   std::vector<double>  lon_coor;
   while (data_lon >> lon)
      lon_coor.push_back(std::atof(lat));
   data_lon.close();


   array_coor c_array;
   double eps = 0;
   for (int i = 0; i < lon_coor.size();++i)
   {
      c_array.push_back(std::make_pair(lat_coor[i], lon_coor[i]));
      if (i != lon_coor.size()-1)
         eps = std::max(std::sqrt(std::pow(lat_coor[i+1] - lat_coor[i], 2) + std::pow(lon_coor[i+1] - lon_coor[i], 2)), eps);
      std::cout << lat_coor[i] << " " << lon_coor[i] << " \n";
   }

   array coor = break_array(c_array, eps);
   c_array = coor[1];
   double dist = std::sqrt(std::pow(c_array[c_array.size()-1].first - c_array[0].first , 2) + std::pow(c_array[c_array.size()-1].second - c_array[0].second, 2));


   array new_coor;
   while (dist>eps)
   {
      new_coor.push_back(coor[1]);
      coor = break_array(coor[0], eps);

      c_array = coor[1];
      dist = std::sqrt(std::pow(c_array[c_array.size()-1].first - c_array[0].first , 2) + std::pow(c_array[c_array.size()-1].second - c_array[0].second, 2));
   }

   return 0;
}

