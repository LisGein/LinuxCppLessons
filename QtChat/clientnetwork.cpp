#include "clientnetwork.h"

ClientNetwork::ClientNetwork(const QByteArray &user_name, const QString& str_host, int nPort)
  : next_block_size_(0)
{
  tcp_socket_ = new QTcpSocket(this);

  tcp_socket_->connectToHost(str_host, nPort);
  connect(tcp_socket_, SIGNAL(connected()), SLOT(slot_connected()));
  connect(tcp_socket_, SIGNAL(readyRead()), SLOT(slot_ready_read()));
  connect(tcp_socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_error(QAbstractSocket::SocketError)));
  tcp_socket_->write(user_name);
}
// First type message - input message client
// Second type message - show online users
void ClientNetwork::slot_ready_read()
{
  QDataStream in(tcp_socket_);
  in.setVersion(QDataStream::Qt_4_2);
  while (true)
    {
      if (!next_block_size_)
        {
          if (tcp_socket_->bytesAvailable() < sizeof(quint16))
            break;
          in >> next_block_size_;
        }

      if (tcp_socket_->bytesAvailable() < next_block_size_)
        break;
      QString str;
      quint8 type_msg;
      in >> type_msg >> str;
      next_block_size_ = 0;
      if (FIRST_TYPE_MSG == type_msg)
        emit in_message(str);
      else if (SECOND_TYPE_MSG == type_msg)
        emit online(str);
    }
}

void ClientNetwork::slot_error(QAbstractSocket::SocketError err)
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

void ClientNetwork::slot_send_message(QByteArray arr_block)
{
  tcp_socket_->write(arr_block);
}

void ClientNetwork::slot_connected()
{
  QString str = "Welcome to chat!";
  emit in_message(str);
}

void ClientNetwork::slot_show_online_cl()
{
  QByteArray  arr_block;
  QDataStream out(&arr_block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << SECOND_TYPE_MSG;
  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  tcp_socket_->write(arr_block);
}
