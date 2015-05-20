#pragma once
#include <QWidget>
#include <QTcpSocket>

class ClientNetwork: public QWidget {
  Q_OBJECT
public:
  ClientNetwork(const QByteArray& user_name,const QString& str_host, int nPort);

public slots:
  void slot_ready_read();
  void slot_error(QAbstractSocket::SocketError err);
  void slot_send_message(QByteArray arrBlock);
  void slot_connected();
  void slot_show_online();

signals:
  void in_message(QString str);
  void online(QString online_users);

private:
  quint16     next_block_size_;
  QTcpSocket* tcp_socket_;
};

