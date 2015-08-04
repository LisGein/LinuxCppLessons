#pragma once
#include <QObject>
#include <QFile>
#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTextStream>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include "rapidjson/error/error.h"
#include <rapidjson/reader.h>
#include "address.h"

class StringServer : public QObject {
   Q_OBJECT
public:
   explicit StringServer(int port, QWidget *parent = 0);
   ~StringServer();
    void send_all(QByteArray msg);
    void send_private(Address address, QByteArray msg);

signals:
   void ready_msg(QByteArray const &message, Address host_sender);
   void delete_user(Address host_sender);

private slots:
   void read();
   void new_connect();
   void disconnect_user();


private:
   QTcpServer* tcp_server_;
   QMap<Address,QTcpSocket*> users_;
   QMap<QTcpSocket*, QByteArray> last_msg_;

   void send_msg(QTcpSocket* tcp_socket, QByteArray msg);
};
