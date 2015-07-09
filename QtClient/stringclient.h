#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

class StringClient : public QObject {
   Q_OBJECT
public:
   explicit StringClient(int port, QObject *parent = 0);
   ~StringClient();
   void send(const QString &msg);
   void login(QString const& msg);

signals:
   void ready_msg(QString const &message);

private slots:
   void read();

private:
   QString last_msg_;
   QTcpSocket* tcp_socket_;
};
