#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include "stringserver.h"


class ChatServer : public QObject
{
   Q_OBJECT

public:
   explicit ChatServer(int port, QObject *parent = 0);
   ~ChatServer();

signals:
   void ready_send(QByteArray msg);

private:
   QTcpServer* tcp_server_;
   StringServer *stringServer_;

   void send_data(QTcpSocket *tcp_socket, QString const& message);

private slots:
   void read_in_data(QByteArray message);
};
