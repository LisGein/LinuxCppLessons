#include "deque.h"
#include "node.h"


template<typename T>
Deque<T>::Deque()
   : size_small_array_(1)
   , head_(nullptr)
   , tail(nullptr)
{
   if (sizeof (T) <= 1)
      size_small_array_ = 16;
   else if (sizeof (T) <= 2 )
      size_small_array_ = 8;
   else if (sizeof (T) <= 4 )
      size_small_array_ = 4;
   else if (sizeof (T) <= 8 )
      size_small_array_ = 2;
}

Deque::push_back()
{
   if (head_ == nullptr)
   {

   }

}

Deque::push_front()
{

}

