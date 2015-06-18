#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include "perceptron.h"

int main()
{
  Perceptron perceptron;
  perceptron.base_read();
  perceptron.learning();
  perceptron.start_learning();
  perceptron.add_other();
  return 0;
}
