#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
class NetworkClient
{
private:
  int port_;
  char player_symb_;
  int sock_server_, listener_;
  int bytes_read_;
  int listen_port_;
  struct sockaddr_in addr_;
  int sock_;
  const int MAX_LEN_RANDOM = 1;
  std::string buf_;

public:
  NetworkClient();
  ~NetworkClient();
  void create_serv(int &port_);
  void create_connect(int &listen_port_);
  char selection_first_player(int &input_symb);
  void send_data(std::string &input_pos, std::string &finish_game);
  std::string recv_data();
};


