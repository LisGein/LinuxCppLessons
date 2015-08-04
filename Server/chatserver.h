#pragma once
#include <QAudioOutput>
#include <QAudioInput>
#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>
#include "stringserver.h"
#include <functional>

typedef std::function<void(rapidjson::Document const &, Address, QByteArray)> message_processor_t;

class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(int port, QObject *parent = 0);
    ~ChatServer();

private slots:
    void read_in_data(QByteArray message, Address host_sender);
    void delete_user(Address host_sender);
    void broadcast_audio();

private:
    QTcpServer* tcp_server_;
    QUdpSocket* udpSocket_;
    StringServer *stringServer_;
    QMap< Address, QString> users_;
    QVector < QUdpSocket* > users_address_;
    QMap< QString, Address> re_users_;
    QMap<QString, message_processor_t> message_processors_map_;
    QAudioOutput *qAudioOutput_;
    QAudioInput *qAudioInput_;

    void send_data(QTcpSocket *tcp_socket, QString const& message);
    void error_parse_msg();
    void process_msg(QByteArray message);
    void private_msg(rapidjson::Document const & doc, Address host_sender, QByteArray message);
    void reg_user(rapidjson::Document const & doc, Address host_sender);
    QByteArray create_msg(QString const& msg);
    void list_online();
};
