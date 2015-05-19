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

signals:
  void in_message(QString str);

private:
  quint16     next_block_size_;
  QTcpSocket* tcp_socket_;
};

