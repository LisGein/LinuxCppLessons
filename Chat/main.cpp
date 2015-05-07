#include "networkserver.h"

int main()
{
  NetworkServer networkserver;
  while(true)
    networkserver.step();

  return 0;
}
