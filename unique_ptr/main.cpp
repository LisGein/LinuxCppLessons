#include <iostream>
#include "unique_ptr.h"
#include <memory>

struct test_class
{
        test_class()
                : i_(0)
        {

        }

        test_class(int i)
                : i_(i)
        {}
        int i(){return i_;}
private:
        int i_;
};


int main()
{

        unique_ptr<test_class> q(new test_class(4));
        std::unique_ptr<test_class> r = std::move(q);
        r.reset();
        std::cout << dynamic_cast<test_class *>(q.get())->i()
                     //<< dynamic_cast<test_class *>(r.get())->i()
                        ;

   return 0;
}

