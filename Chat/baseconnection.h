#pragma once

#include <cstdio>
namespace
{
  const size_t BUFFER_SIZE = 3;
}
struct BaseConnection
{
  virtual ~BaseConnection() {}
  virtual void step() = 0;

protected:
  int sock_;
};
