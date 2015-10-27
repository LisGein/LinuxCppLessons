#pragma once
#include "node.h"

template<typename T>
class PartData
{
public:
   PartData();
   void push_back(T* new_node);
   void push_front(T* new_node);
   void pop_back();
   void pop_front();

private:
  int  size_;
  int type_size_;
  Node* data_;
  Node* tail_;
  Node* head_;

};

