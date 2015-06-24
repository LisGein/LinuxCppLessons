#include <iostream>
#include "perceptron.h"
#include "dataset_t.h"

const size_t X_SIZE = 256;
const size_t Y_SIZE = 10;
const size_t EPOCH_COUNT = 100;

int main()
{

    dataset_t dataset("dat.txt", X_SIZE, Y_SIZE);
    dataset.split_train_test(0.7);

    perceptron_t perceptron(dataset.dim());

    for (size_t i = 0; i <  EPOCH_COUNT; ++i)
    {
        size_t correct_train = 0;
        for(auto const &sample: dataset.train_dataset())
        {
            bool correct = perceptron.learn(sample);
            if (correct)
                correct_train += 1;
        }

        size_t correct_test = 0;
        for(auto const &sample: dataset.test_dataset())
        {
            bool correct = perceptron.classify(sample.first) == sample.second;
            if (correct)
                correct_test += 1;
        }

        std::cout << "train precision: " << (double)correct_train / dataset.train_dataset().size() * 100;
        std::cout << " train precision: " << (double)correct_test / dataset.test_dataset().size() * 100 << std::endl;
    }
    return 0;
}
