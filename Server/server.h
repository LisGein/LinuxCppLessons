#pragma once
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>


class Server : public QObject
{
   Q_OBJECT

public:
   explicit Server(int port, QString const& IP_address, QWidget *parent = 0);
   ~Server();

private:
   QTcpServer* tcp_server_;

   void send_data(QTcpSocket *tcp_socket, QString const& message);
private slots:
   void new_connect();
   void read_in_data();
   void disconnect_user();

};

