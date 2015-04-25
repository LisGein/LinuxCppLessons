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
  std::cout << "Input cmd\n";
  std::cin >> role;
  std::unique_ptr<IConnection> connection;
  if (role == "host")
    connection.reset(new NetworkServer(atoi(argv[2])));
  else
    connection.reset(new NetworkClient(atoi(argv[2])));
  Game game(connection.get());
  while(!game.finish())
<<<<<<< HEAD
    {
      game.make_step();
    }
=======
  {
    game.make_step();
  }
  game.show_result();
>>>>>>> parent of 38dd662... Надеюсь всё сохранилось сейчас
  return 0;
}
