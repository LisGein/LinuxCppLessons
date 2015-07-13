#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>

std::mutex mtx;

void f1(int& n)
{
    mutex_.lock();
    for (int i = 0; i < 1000000; ++i)
        n = n + 1;
    mutex_.unlock();
}


int main()
{
    int n = 0;

    std::thread t1(f1, std::ref(n)); // pass by reference
    std::thread t2(f1, std::ref(n)); // pass by reference

    t1.join();
    t2.join();
    std::cout << "Final value of n is " << n << '\n';
}
