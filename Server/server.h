#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include "stringserver.h"


class Server : public QObject
{
   Q_OBJECT

public:
   explicit Server(int port);
   ~Server();

signals:
   void ready_send(QString msg);
private:
   QTcpServer* tcp_server_;
   QString last_msg_;
   StringServer *stringServer_;

   void send_data(QTcpSocket *tcp_socket, QString const& message);

private slots:
   void read_in_data(QString const &message);
};

