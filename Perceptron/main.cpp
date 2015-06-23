#include <iostream>
#include "perceptron.h"

const size_t EPOCH_COUNT = 100;
int main()
{
  Perceptron perceptron;
  perceptron.create_weight();
  int correct;
  int size;
  for (size_t i = 0; i <  EPOCH_COUNT; ++i)
    {
      correct = perceptron.learning("data.txt","learning.txt");
      size = perceptron.size_in_data();
      std::cout << correct << "   " << size << std::endl;

      correct = perceptron.test("data.txt", "test.txt");
      size = perceptron.size_in_data();
      std::cout << correct << "   " << size << std::endl;
      std::cout << "   " << std::endl;
    }
  return 0;
}
