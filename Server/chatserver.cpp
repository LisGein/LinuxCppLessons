#include "chatserver.h"
#include "stringserver.h"

ChatServer::ChatServer(int port)
   : tcp_server_(new QTcpServer(this))
{

   stringServer_ = new StringServer(port);
   connect(stringServer_, SIGNAL(ready_msg(QString)), this, SLOT(read_in_data(QString)));
   connect(this, SIGNAL(ready_send(QString)), stringServer_, SLOT(send_all(QString)));
}

ChatServer::~ChatServer()
{
}

void ChatServer::read_in_data(const QString &message)
{
   rapidjson::Document d;
   d.Parse(message.toUtf8());
   //qDebug() << "message body: " << d["msg"].GetString();
   emit ready_send(message );
}
