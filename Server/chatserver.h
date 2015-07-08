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

private slots:
   void read_in_data(QByteArray message, QHostAddress const& host_sender, quint16 port_sender);
   void delete_user(QHostAddress const& host_sender, quint16 port_sender);

private:
   QTcpServer* tcp_server_;
   StringServer *stringServer_;
   QMap< quint16, QString> users_;
   QMap< QString, quint16> re_users_;

   void send_data(QTcpSocket *tcp_socket, QString const& message);
   QString find_receiver_nick(QString const& msg);
   void error_parse_msg();
   QByteArray create_msg(QString const& msg);
   void send_private_msg(QByteArray const& message, QString const& msg, QHostAddress const& host_sender, quint16 port_sender);
   void connect_new_user(QString text_message, QHostAddress const& host_sender, quint16 port_sender);
};
