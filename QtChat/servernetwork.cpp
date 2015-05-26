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


void ServerNetwork::slot_send_to_server(QByteArray  arr_block)
{
  tcp_socket_->write(arr_block);
}

void ServerNetwork::slot_delete_user(QTcpSocket *socket_del_user)
{
  auto it_users_port_ = connected_users_port_.find(socket_del_user);
  if (it_users_port_ != connected_users_port_.end())
    {
      QString msg_user_disconnect = "You are banned!";
      send_to_client(socket_del_user, msg_user_disconnect + " ", FIRST_TYPE);
      socket_del_user->disconnect();
      re_connected_users_port_.remove(it_users_port_.value());
      msg_user_disconnect = it_users_port_.value() + " has been banned.";
      disconnect_client(socket_del_user, msg_user_disconnect);
      emit refresh(re_connected_users_port_);
    }
}

void ServerNetwork::slot_new_connection()
{
  QTcpSocket* client_socket = tcp_server_->nextPendingConnection();
  connect(client_socket, SIGNAL(disconnected()), this, SLOT(slot_disconnect_user()));
  connect(client_socket, SIGNAL(readyRead()), this, SLOT(slot_read_in_message()));

  send_to_client(client_socket, "Server Response: Connected!", FIRST_TYPE);
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

void ServerNetwork::slot_disconnect_user()
{
  QTcpSocket* client_socket = (QTcpSocket*)sender();
  auto it_users_port_ = connected_users_port_.find(client_socket);
  if (it_users_port_ != connected_users_port_.end())
    {
      QString msg_user_disconnect = it_users_port_.value() + " disconnected.";
      re_connected_users_port_.remove(it_users_port_.value());
      disconnect_client(client_socket, msg_user_disconnect);
    }
}

void ServerNetwork::slot_connected()
{
  QString msg_connect = "Received the connected() signal";
  emit in_message(msg_connect);
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

void ServerNetwork::slot_refresh()
{
  emit refresh(re_connected_users_port_);
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

void ServerNetwork::read_msg(QString str, QTcpSocket* client_socket)
{
  auto it_users_port_ = connected_users_port_.find(client_socket);
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
      re_connected_users_port_.insert(str, client_socket);
      connected_users_port_.insert(client_socket,str);
      message = str + " connected.";
      emit in_message(message);

      next_block_size_ = 0;
      for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
        send_to_client(it_users_port_.key(), message + " " , FIRST_TYPE);

        emit refresh(re_connected_users_port_);
    }
}

void ServerNetwork::forming_list_online(QTcpSocket* client_socket)
{
  QString users;
  for (auto it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
    users += it_users_port_.value() + "\n";
  next_block_size_ = 0;
  send_to_client(client_socket, users , SECOND_TYPE);
}

void ServerNetwork::disconnect_client(QTcpSocket* socket_del_user, QString msg_user_disconnect)
{
  emit in_message(msg_user_disconnect);
  connected_users_port_.remove(socket_del_user);
  socket_del_user->deleteLater();
  for (auto it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
    send_to_client(it_users_port_.key(), msg_user_disconnect + " ", FIRST_TYPE);
    emit refresh(re_connected_users_port_);
}


