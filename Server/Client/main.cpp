#include <iostream>
#include <stdlib.h>
#include "networkclient.h"
#include "games.h"
#include <random>

int main()
{
  Games games;
  NetworkClient client;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> random_range(0, 999);
  int random_numb(random_range(gen));

  int port, listen_port;
  std::cout << "Input your port\n";
  std::cin >> port;
  client.create_serv(port);
  std::cout << "Input port second player\n";
  std::cin >> listen_port;
  client.create_connect(listen_port);
  int sock = client.return_sock();
  games.set_sock(sock);
  char player_symb = client.selection_first_player(random_numb);
  games.set_symb(player_symb);
  std::string status_game;
  status_game = "0";
  while (!games.finish_play())
  {
      if (player_symb == 'o')
      {
          std::string buf = client.recv_data();
          status_game = client.recv_data();
          games.send_data(buf);
          player_symb = 'x';
      }
    std::string input_pos = games.make_step();
    if (games.finish_play() == true)
      status_game = "1";
    client.send_data(input_pos, status_game);
    if (status_game == "1")
      {
        std::cout << "You win!\n";
        break;
      }
    std::string buf = client.recv_data();
    status_game = client.recv_data();
    if (status_game == "1")
      {
        std::cout << "You lose!\n";
        break;
      }
    games.send_data(buf);
  }
  return 0;
}
