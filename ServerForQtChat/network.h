#pragma once
#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>
#include <QListWidget>

class ServerNetwork: public QWidget {
  Q_OBJECT
public:
  ServerNetwork(QString const& str_host, int port);

private slots:
  void slot_send_to_server(QByteArray arr_block);
  void slot_new_connection();
  void slot_read_in_message();
  void slot_disconnect_user();

private:
  void send_to_client(QTcpSocket* socket, const QString& str, quint8 Types);
  void read_msg(QString str, QTcpSocket *client_socket);
  void forming_list_online(QTcpSocket* client_socket);
  void disconnect_client(QTcpSocket* socket_del_user, QString msg_user_disconnect);

  quint16     next_block_size_;
  QTcpServer* tcp_server_;
  QTcpSocket* tcp_socket_;
  QMap<QTcpSocket*, QString> connected_users_port_;
  QMap<QString, QTcpSocket*> re_connected_users_port_;
  const quint8 FIRST_TYPE = 0;
  const quint8 SECOND_TYPE = 1;
};

