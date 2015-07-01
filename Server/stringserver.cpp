#include "stringserver.h"

StringServer::StringServer(int port, const QString &IP_address)
{
   tcp_server_ = new QTcpServer;
   if (!tcp_server_->listen(QHostAddress(IP_address), port))
   {
      tcp_server_->close();
      return;
   }
   connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(new_connect()));
}

StringServer::~StringServer()
{

}

void StringServer::disconnect_user()
{
   QTcpSocket* tcp_socket;
   tcp_socket = static_cast<QTcpSocket*>(sender());
   tcp_socket->deleteLater();
}

void StringServer::new_connect()
{
   while (tcp_server_->hasPendingConnections())
   {
      QTcpSocket* tcp_socket = tcp_server_->nextPendingConnection();
      connect(tcp_socket, SIGNAL(readyRead()), SLOT(read()));
      connect(tcp_socket, SIGNAL(disconnected()), SLOT(disconnect_user()));
      users_.push_back(tcp_socket);
   }
}

void StringServer::send_all(QString msg)
{
   for (int i = 0; i < users_.size(); ++i)
   {
      QTextStream stream(users_[i]);
      stream.setCodec("UTF-8");
      QByteArray in_data;
      in_data.append(msg);
      stream << in_data;
   }
}

void StringServer::read()
{
   QByteArray in_data;
   QTcpSocket* tcp_socket;
   tcp_socket = static_cast<QTcpSocket*>(sender());
   QTextStream stream(tcp_socket);
   stream.setCodec("UTF-8");
   in_data.append( stream.readAll());
   emit ready_msg(in_data);

}
