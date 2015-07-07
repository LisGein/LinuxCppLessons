#include "chatserver.h"
#include "stringserver.h"


ChatServer::ChatServer(int port, QObject *parent)
    : tcp_server_(new QTcpServer(this))
{

    stringServer_ = new StringServer(port);
    connect(stringServer_, SIGNAL(ready_msg(QByteArray)), this, SLOT(read_in_data(QByteArray)));
    connect(this, SIGNAL(ready_send(QByteArray)), stringServer_, SLOT(send_all(QByteArray)));
}

ChatServer::~ChatServer()
{
}

void ChatServer::read_in_data(QByteArray message)
{
    rapidjson::Document doc;
    doc.Parse(message);
    bool fail_parse = doc.HasParseError();
    if (fail_parse)
        qDebug() << "error parse message";
    else
        emit ready_send(message );
}
