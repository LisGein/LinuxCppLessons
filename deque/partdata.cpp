#include "partdata.h"


template<typename T>
PartData<T>::PartData()
   :size_(0)
   , type_size_(1)
   , tail_(nullptr)
   , head(nullptr)
{
   if (sizeof (T) <= 1)
      type_size_ = 16;
   else if (sizeof (T) <= 2 )
      type_size_ = 8;
   else if (sizeof (T) <= 4 )
      type_size_ = 4;
   else if (sizeof (T) <= 8 )
      type_size_ = 2;
   data_ = new Node[type_size_];
}

template<typename T>
void PartData::push_back(T* new_node)
{
   Node* node = new Node();
   node->data_ = new_node;
   if (size_ != 0)
   {
      node->prev_ = tail_;
   }
   else
   {
      head_ = node;
   }
   tail_ = node;
   data_[size_] = node;
      ++size_;
}

template<typename T>
void PartData::push_front(T* new_node)
{
   Node* node = new Node();
   node->data_ = new_node;
   if (size_ != 0)
   {
      node->next_ = head_;
   }
   else
   {
      tail_ = node;
   }
   head_ = node;
   data_[size_] = node;
   ++size_;
}

template<typename T>
void PartData::pop_back()
{
   if (size_ == 1)
   {
      tail_ = nullptr;
      head_ = nullptr;
   }
   else
   {
   }
      --size_;
}

template<typename T>
void PartData::pop_front()
{
   if (size_ == 1)
   {
      tail_ = nullptr;
      head_ = nullptr;
   }
   else
   {
   }
      --size_;
}

