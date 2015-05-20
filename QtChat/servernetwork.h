#pragma once
#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>

class ServerNetwork: public QWidget {
  Q_OBJECT
public:
  ServerNetwork(const QByteArray& user_name, QString const& str_host, int port);

public slots:
  void slot_new_connection();
  void slot_read_in_message();
  void slot_disconnect_user();
  void slot_show_online();

  void slot_connected();
  void slot_error(QAbstractSocket::SocketError);
  void slot_send_to_server(QByteArray arr_block);

signals:
  void in_message(QString str);
  void online(QString online_users);

private:
  void send_to_client(QTcpSocket* socket, const QString& str);

  quint16     next_block_size_;
  QTcpServer* tcp_server_;
  QTcpSocket* tcp_socket_;
  QMap<QTcpSocket*, QString> connected_users_port_;
  QMap<QTcpSocket*, QString>::const_iterator it_users_port_;
};

