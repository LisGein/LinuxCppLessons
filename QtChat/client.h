#pragma once
#include <QWidget>
#include <QTcpSocket>

class QTextEdit;
class QLineEdit;

class Client : public QWidget {
Q_OBJECT
private:
    QTcpSocket* tcp_socket_;
    QTextEdit*  out_text_;
    QLineEdit*  in_text_;
    quint16     next_block_size_;

public:
    Client(const QByteArray& user_name, const QString& strHost, int nPort, QWidget* pwgt = 0) ;
    QByteArray user_name_;

private slots:
    void slot_ready_read();
    void slot_error(QAbstractSocket::SocketError);
    void slot_send_to_server();
    void slot_connected();
};
