#include <stdlib.h>
#include <iostream>
#include "baseconnection.h"
#include "networkserver.h"
#include "networkclient.h"
#include <memory>

int main(int argc, char ** argv)
{
  std::string role(argv[1]);

  BaseConnection* connection;
  if (role == "host")
      connection = new NetworkServer;
  else
      connection = new NetworkClient;
  while(true)
    connection->step();

  return 0;
}
