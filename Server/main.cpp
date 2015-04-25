#include <stdlib.h>
#include <iostream>
#include <memory>
#include "networkclient.h"
#include "networkserver.h"
#include "iconnection.h"
#include "game.h"

int main(int argc, char ** argv)
{
  std::string role(argv[1]);
  std::unique_ptr<IConnection> connection;
  if (role == "host")
    connection.reset(new NetworkServer(atoi(argv[2])));
  else
    connection.reset(new NetworkClient(atoi(argv[2])));
  Game game(connection.get());
  while(!game.finish())
  {
    game.make_step();
  }
  return 0;
}
