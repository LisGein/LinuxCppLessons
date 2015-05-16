#include "server.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include  <QPushButton>
#include  <QLineEdit>

Server::Server(const QByteArray& user_name, const QString& strHost, int nPort, QWidget *pwgt)
  :QWidget(pwgt)
  , next_block_size_(0)
  , user_name_(user_name)
{
  tcp_server_ = new QTcpServer(this);
  if (!tcp_server_->listen(QHostAddress::Any, nPort))
    {
      QMessageBox::critical(0, "Server Error", "Unable to start the server:" + tcp_server_->errorString());
      tcp_server_->close();
      return;
    }
  connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(slot_new_connection()));

  tcp_socket_ = new QTcpSocket(this);

  tcp_socket_->connectToHost(strHost, nPort);
  connect(tcp_socket_, SIGNAL(connected()), SLOT(slot_connected()));
  connect(tcp_socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_error(QAbstractSocket::SocketError)));
  out_text_ = new QTextEdit;
  in_text_ = new QLineEdit;
  out_text_->setReadOnly(true);
  in_text_->setFixedSize(400, 50);

  connect(in_text_, SIGNAL(returnPressed()), this, SLOT(slot_send_to_server()));

  QPushButton* in_cmd = new QPushButton("&Send");
  connect(in_cmd, SIGNAL(clicked()), SLOT(slot_send_to_server()));

  //Layout setup
  QVBoxLayout* window_layout = new QVBoxLayout;
  window_layout->addWidget(new QLabel("<H1>Server</H1>"));
  window_layout->addWidget(out_text_);
  window_layout->addWidget(in_text_);
  window_layout->addWidget(in_cmd);
  setLayout(window_layout);
  tcp_socket_->write(user_name_);
}
void Server::slot_new_connection()
{
  QTcpSocket* client_socket = tcp_server_->nextPendingConnection();
  connect(client_socket, SIGNAL(disconnected()), client_socket, SLOT(deleteLater()));
  connect(client_socket, SIGNAL(readyRead()), this, SLOT(slot_read_message()));

  send_to_client(client_socket, "Server Response: Connected!");

}
void Server::slot_read_message()
{
  QTcpSocket* pClientSocket = (QTcpSocket*)sender();
  QDataStream in(pClientSocket);
  in.setVersion(QDataStream::Qt_4_2);
  while (true)
    {
      if (!next_block_size_)
        {
          if (pClientSocket->bytesAvailable() < sizeof(quint16))
            break;
          in >> next_block_size_;
        }
      if (pClientSocket->bytesAvailable() < next_block_size_)
        break;

      QString str;
      QTime   time;
      in >> time >> str;

      it_users_port_ = connected_users_port_.find(pClientSocket);
      if (it_users_port_ != connected_users_port_.end())
        {
          QString strMessage =
              time.toString() + " " + connected_users_port_[pClientSocket] + ": " +
              str;
          out_text_->append(strMessage);

          next_block_size_ = 0;
          for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
            send_to_client(it_users_port_.key(), strMessage + " " );
        }
      else
        {
          connected_users_port_.insert(pClientSocket,str);
          QString strMessage = str + " connected.";
          out_text_->append(strMessage);

          next_block_size_ = 0;
          for (it_users_port_ = connected_users_port_.begin(); it_users_port_ != connected_users_port_.end(); ++it_users_port_)
            send_to_client(it_users_port_.key(), strMessage + " " );
        }
    }
}
void Server::send_to_client(QTcpSocket* pSocket, const QString& str)
{
  QByteArray  arrBlock;
  QDataStream out(&arrBlock, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << QTime::currentTime() << str;

  out.device()->seek(0);
  out << quint16(arrBlock.size() - sizeof(quint16));

  pSocket->write(arrBlock);
}

void Server::slot_error(QAbstractSocket::SocketError err)
{
  QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                    "The host was not found." :
                                    err == QAbstractSocket::RemoteHostClosedError ?
                                      "The remote host is closed." :
                                      err == QAbstractSocket::ConnectionRefusedError ?
                                        "The connection was refused." :
                                        QString(tcp_socket_->errorString())
                                        );
  out_text_->append(strError);
}
void Server::slot_send_to_server()
{
  QByteArray  arrBlock;
  QDataStream out(&arrBlock, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << QTime::currentTime() << in_text_->text();

  out.device()->seek(0);
  out << quint16(arrBlock.size() - sizeof(quint16));

  tcp_socket_->write(arrBlock);
  in_text_->setText("");
}
void Server::slot_connected()
{
  out_text_->append("Received the connected() signal");
}
