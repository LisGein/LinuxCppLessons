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
    void send_all(QByteArray msg);
    void send_private(quint16 port_user, QByteArray msg);

signals:
   void ready_msg(QByteArray const &message, QHostAddress const &host_sender, quint16 port_sender);
   void delete_user(QHostAddress const &host_sender, quint16 port_sender);

private slots:
   void read();
   void new_connect();
   void disconnect_user();

private:
   QTcpServer* tcp_server_;
   QMap<quint16,QTcpSocket*> users_;
   QMap<QTcpSocket*, QByteArray> last_msg_;

   void send_msg(QTcpSocket* tcp_socket, QByteArray msg);
};
