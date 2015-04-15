#include <stdlib.h>
#include "networkclient.h"
#include "games.h"

int main()
{
  Games games;
  NetworkClient client;
  client.connecting();

  while (!games.finish_play())
  {
    client.send_recv();
  }
  client.end_connect();
  return 0;
}
