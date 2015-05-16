#pragma once
#include <QWidget>
#include <QTcpServer>
#include <QTextEdit>
#include <QTcpSocket>
#include <QLineEdit>
#include <QMap>

class Server : public QWidget {
  Q_OBJECT
  QTcpServer* tcp_server_;
  QTcpSocket* tcp_socket_;
  QTextEdit*  out_text_;
  QLineEdit*  in_text_;
  quint16     next_block_size_;

private:
  QByteArray user_name_;
  QTcpSocket* client_socket;
  QMap<QTcpSocket*, QString> connected_users_port_;
  QMap<QTcpSocket*, QString>::const_iterator it_users_port_;

private:
  void send_to_client(QTcpSocket* pSocket, const QString& str);

public:
  Server(const QByteArray& user_name, const QString& strHost, int nPort, QWidget* pwgt = 0) ;


public slots:
  void slot_new_connection();
  void slot_read_message();
  void slot_disconnect_user();

  void slot_error(QAbstractSocket::SocketError);
  void slot_send_to_server();
  void slot_connected();
};
