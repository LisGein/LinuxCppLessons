#include "server.h"
#include "stringserver.h"

Server::Server(int port)
   : tcp_server_(new QTcpServer(this))
{

   stringServer_ = new StringServer(port, IP_address);

   connect(stringServer_, SIGNAL(ready_msg(QString)), this, SLOT(read_in_data(QString)));
   connect(this, SIGNAL(ready_send(QString)), stringServer_, SLOT(send_all(QString)));
}

Server::~Server()
{
}

void Server::read_in_data(const QString &message)
{
   QByteArray in_data;
   QTcpSocket* tcp_socket;
   tcp_socket = static_cast<QTcpSocket*>(sender());
   QTextStream stream(tcp_socket);
   stream.setCodec("UTF-8");
   in_data.append( message);
   int  size_msg = in_data.size() - 1;
   last_msg_ += in_data;
   qDebug() << "Recv data: " << in_data;
   if (in_data[size_msg] == '\n')
   {
      emit ready_send(last_msg_ );
      last_msg_.clear();
   }
}

