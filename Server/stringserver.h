#pragma once
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include "rapidjson/document.h"

class StringServer : public QObject {
   Q_OBJECT
public:
   explicit StringServer(int port, QString const& IP_address);
   ~StringServer();
signals:
   void ready_msg(QString const &message);

private slots:
   void send_all(QString msg);
   void read();
   void new_connect();
   void disconnect_user();

private:
   QTcpServer* tcp_server_;
   QVector<QTcpSocket*> users_;
};
