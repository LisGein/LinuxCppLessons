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
   QString nick_name();


signals:
   void ready_msg(QString const &message);
   void ready_private_msg(QString const &message);
   void ready_online(rapidjson::Document const & doc);

private slots:
   void read();
   void request_list_online();
   void login(QString const& name, QString const& IP);

private:
   QString nick_user_;
   QString last_msg_;
   QTcpSocket* tcp_socket_;
   int port_;

   void generete_doc(QMap<QString, QString> message);
};
