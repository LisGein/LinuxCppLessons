#include <iostream>
#include "perceptron.h"
#include "dataset_t.h"
#include "confusion_matrix.h"


const size_t X_SIZE = 256;
const size_t Y_SIZE = 10;
const size_t EPOCH_COUNT = 100;

int main()
{
    dataset_t dataset("dat.txt", X_SIZE, Y_SIZE);
    dataset.split_train_test(0.7);
    ConfusionMatrix confusion_matrix(Y_SIZE);

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
            std::vector<char> return_classify = perceptron.classify(sample.first);
            bool correct = return_classify == sample.second;
            if (correct)
                correct_test += 1;
            confusion_matrix.incrementacia(return_classify, sample.second);
        }

        double F = confusion_matrix.f_1();
        std::cout << "test train precision: " << F << std::endl;
        confusion_matrix.clear_confusion_matrix();
    }
    return 0;
}
