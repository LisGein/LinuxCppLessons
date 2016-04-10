#pragma once
#include "auto_ptr.h"
#include <utility>

template<typename T>
class unique_ptr
{
public:
        unique_ptr(T *obj)
                : obj_(obj)
        {

        }
        virtual ~unique_ptr(){}
        T *get(){return obj_;}
        T &operator =(const T &) = delete;
        void reset(T *ptr = nullptr)
        {
                std::swap(ptr, this);
                if (ptr != nullptr)
                {

                }

        }
        unique_ptr(unique_ptr&& other)
        {
                obj_ = other.obj_;
                other.obj_ = nullptr;
        }

//private:
        T *obj_;
};

