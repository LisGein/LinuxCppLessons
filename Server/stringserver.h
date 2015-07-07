#pragma once
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include "rapidjson/error/error.h"
#include <rapidjson/reader.h>

class StringServer : public QObject {
   Q_OBJECT
public:
   explicit StringServer(int port, QWidget *parent = 0);
   ~StringServer();
signals:
   void ready_msg(QByteArray const &message);

private slots:
   void send_all(QByteArray msg);
   void read();
   void new_connect();
   void disconnect_user();

private:
   QTcpServer* tcp_server_;
   QVector<QTcpSocket*> users_;
   QMap<QTcpSocket*, QByteArray> last_msg_;
};
