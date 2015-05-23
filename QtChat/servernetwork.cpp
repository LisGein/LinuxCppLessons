#include "servernetwork.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include  <QPushButton>
#include  <QLineEdit>

ServerNetwork::ServerNetwork(const QByteArray& user_name, QString const& str_host, int port)
  : next_block_size_(0)
{
  tcp_server_ = new QTcpServer(this);
  if (!tcp_server_->listen(QHostAddress::Any, port))
    {
      QMessageBox::critical(0, "Server Error", "Unable to start the server:" + tcp_server_->errorString());
      tcp_server_->close();
      return;
    }
  connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(slot_new_connection()));

  tcp_socket_ = new QTcpSocket(this);
  tcp_socket_->connectToHost(str_host, port);
  connect(tcp_socket_, SIGNAL(connected()), SLOT(slot_connected()));
  connect(tcp_socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_error(QAbstractSocket::SocketError)));
  tcp_socket_->write(user_name);
}
// First type message - input message client
// Second type message - show online users
// Third type message - disconnect user
void ServerNetwork::slot_new_connection()
{
  QTcpSocket* client_socket = tcp_server_->nextPendingConnection();
  connect(client_socket, SIGNAL(disconnected()), this, SLOT(slot_disconnect_user()));
  connect(client_socket, SIGNAL(readyRead()), this, SLOT(slot_read_in_message()));

  send_to_client(client_socket, "Server Response: Connected!", FIRST_TYPE);
}

void ServerNetwork::slot_disconnect_user()
{
  QTcpSocket* client_socket = (QTcpSocket*)sender();
  it_users_port_ = connected_users_port_.find(client_socket);
  QString name = it_users_port_.value() + " disconnected.";
  emit in_message(name);
  connected_users_port_.remove(client_socket);
  client_socket->deleteLater();

  for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
    send_to_client(it_users_port_.key(), name + " ", FIRST_TYPE);

}

void ServerNetwork::slot_read_in_message()
{
  QTcpSocket* client_socket = (QTcpSocket*)sender();
  QDataStream in(client_socket);
  in.setVersion(QDataStream::Qt_4_2);
  while (true)
    {

      if (!next_block_size_)
        {
          if (client_socket->bytesAvailable() < sizeof(quint16))
            break;
          in >> next_block_size_;
        }
      if (client_socket->bytesAvailable() < next_block_size_)
        break;

      quint8 type_msg;
      in >> type_msg;
      if (FIRST_TYPE == type_msg)
        {
          QString str;
          in >> str;
          read_msg(str, client_socket);
        }
      else if (SECOND_TYPE == type_msg)
        forming_list_online(client_socket);
    }
}
void ServerNetwork::read_msg(QString str, QTcpSocket* client_socket)
{
  it_users_port_ = connected_users_port_.find(client_socket);
  QString message;
  if (it_users_port_ != connected_users_port_.end())
    {
      message = connected_users_port_[client_socket] + ": " + str;
      emit in_message(message);

      next_block_size_ = 0;
      for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
        send_to_client(it_users_port_.key(), message + " " , FIRST_TYPE);
    }
  else
    {
      connected_users_port_.insert(client_socket,str);
      message = str + " connected.";
      emit in_message(message);

      next_block_size_ = 0;
      for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
        send_to_client(it_users_port_.key(), message + " " , FIRST_TYPE);
    }
}

void ServerNetwork::forming_list_online(QTcpSocket* client_socket)
{
  QString users;
  for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
    users += it_users_port_.value() + "\n";
  next_block_size_ = 0;
  send_to_client(client_socket, users , SECOND_TYPE);
}

void ServerNetwork::send_to_client(QTcpSocket* socket, const QString& str, quint8 Types)
{
  QByteArray  arr_block;
  QDataStream out(&arr_block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << Types << str;

  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));

  socket->write(arr_block);
}

void ServerNetwork::slot_error(QAbstractSocket::SocketError err)
{
  QString str_error = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                     "The host was not found." :
                                     err == QAbstractSocket::RemoteHostClosedError ?
                                       "The remote host is closed." :
                                       err == QAbstractSocket::ConnectionRefusedError ?
                                         "The connection was refused." :
                                         QString(tcp_socket_->errorString())
                                         );
  emit in_message(str_error);
}


void ServerNetwork::slot_send_to_server(QByteArray  arr_block)
{
  tcp_socket_->write(arr_block);
}

void ServerNetwork::slot_connected()
{
  QString msg_connect = "Received the connected() signal";
  emit in_message(msg_connect);
}

void ServerNetwork::slot_show_online()
{
  QString online_users;
  for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
    online_users += it_users_port_.value() + "\n";
  emit online(connected_users_port_);
}
