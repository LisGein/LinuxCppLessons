#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include "stringserver.h"
#include <functional>

typedef std::function<void(rapidjson::Document const &, QHostAddress const&, quint16, QByteArray)> message_processor_t;

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
    QMap<QString, message_processor_t> message_processors_map_;

    void send_data(QTcpSocket *tcp_socket, QString const& message);
    void error_parse_msg();
    void process_msg(QByteArray message);
    void private_msg(rapidjson::Document const & doc, QHostAddress const& host_sender, quint16 port_sender, QByteArray message);
    void reg_user(rapidjson::Document const & doc, QHostAddress const& host_sender, quint16 port_sender);
    QByteArray create_msg(QString const& msg);
    void list_online();
};
