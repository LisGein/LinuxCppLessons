#include "clientnetwork.h"
#include <QTime>

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
      QTime   time;
      QString str;
      in >> time >> str;
      next_block_size_ = 0;
      emit in_message(str);
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
