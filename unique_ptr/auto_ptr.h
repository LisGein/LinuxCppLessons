#pragma once

template<typename T>
class auto_ptr
{
public:
        auto_ptr(T *obj)
                : object_(obj)
        {

        }
        //auto_ptr(const auto_ptr<T> &obj_ptr);
        virtual ~auto_ptr()
        {
                delete object_;
        }
       virtual  T *operator =(T *other)
        {
               other = object_;
                object_ = nullptr;
                return other;
        }
        virtual T *get()
        {
                return object_;
        }

private:
        T *object_;
};

