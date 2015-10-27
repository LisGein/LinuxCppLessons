#pragma once
#include "partdata.h"

template<typename T>
class Node
{
       friend class PartData;
public:
   Node();

private:
   Node* prev_;
   Node* next_;
   T* data_;
};

