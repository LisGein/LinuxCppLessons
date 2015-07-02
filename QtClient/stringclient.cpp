#include "stringclient.h"
#include <QHostAddress>

StringClient::StringClient(int port)
   :last_msg_("")
{
   tcp_socket_ = new QTcpSocket;
   tcp_socket_->connectToHost("localhost", port);
   connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(read()));
}

StringClient::~StringClient()
{

}

void StringClient::send(QString msg)
{
   QByteArray array_msg;;
   array_msg.append("{\"msg\":\""+msg+"\"}\n");
   tcp_socket_->write(array_msg);
}

void StringClient::read()
{
   while (tcp_socket_->bytesAvailable() > 0)
   {
      last_msg_ += tcp_socket_->readLine();
      if (last_msg_[last_msg_.size() -1] == '\n')
      {
         emit ready_msg(last_msg_);
         last_msg_ = "";
      }
   }
}
