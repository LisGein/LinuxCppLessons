#include "server.h"

Server::Server(int port)
   : tcp_server_(new QTcpServer(this))
{
   if (!tcp_server_->listen(QHostAddress::Any, port))
   {
      tcp_server_->close();
      return;
   }
   connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(new_connect()));
}

Server::~Server()
{

}

void Server::new_connect()
{
   while (tcp_server_->hasPendingConnections())
   {
      QTcpSocket* tcp_socket = tcp_server_->nextPendingConnection();
      connect(tcp_socket, SIGNAL(readyRead()), SLOT(read_in_data()));
      connect(tcp_socket, SIGNAL(disconnected()), SLOT(disconnect_user()));
      qDebug() << "Client " << tcp_socket->peerAddress() <<  " connected to server";
   }
}

void Server::disconnect_user()
{
   QTcpSocket* tcp_socket;
   tcp_socket = static_cast<QTcpSocket*>(sender());
   qDebug() << "Client " << tcp_socket->peerAddress() <<  " disconnected";
   tcp_socket->deleteLater();
}

void Server::read_in_data()
{
   QTcpSocket* tcp_socket;
   tcp_socket = static_cast<QTcpSocket*>(sender());
   while (tcp_socket->bytesAvailable() > 0)
   {
      QString in_data = tcp_socket->readAll();
      send_data(tcp_socket, in_data);
   }
}

void Server::send_data(QTcpSocket* tcp_socket, QString const& message)
{
   QByteArray send_message;
   send_message.append(message);
   tcp_socket->write(send_message);
}
