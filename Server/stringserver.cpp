#include "stringserver.h"

StringServer::StringServer(int port, QWidget *parent)
    :tcp_server_(new QTcpServer(this))
{
    if (!tcp_server_->listen(QHostAddress::Any, port))
    {
        tcp_server_->close();
        return;
    }
    connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(new_connect()));
}

StringServer::~StringServer()
{

}

void StringServer::disconnect_user()
{
    QTcpSocket* tcp_socket;
    tcp_socket = static_cast<QTcpSocket*>(sender());
    tcp_socket->deleteLater();
    last_msg_.remove(tcp_socket);
    Address address(tcp_socket->peerAddress(), tcp_socket->peerPort());
    users_.remove(address);
    emit delete_user(address);
}

void StringServer::new_connect()
{
    while (tcp_server_->hasPendingConnections())
    {
        QTcpSocket* tcp_socket = tcp_server_->nextPendingConnection();
        connect(tcp_socket, SIGNAL(readyRead()), SLOT(read()));
        connect(tcp_socket, SIGNAL(disconnected()), SLOT(disconnect_user()));
        Address address(tcp_socket->peerAddress(), tcp_socket->peerPort());
        users_.insert(address, tcp_socket);
        last_msg_.insert(tcp_socket, "");
    }
}

void StringServer::send_all(QByteArray msg)
{
    for (auto i = users_.begin(); i != users_.end(); ++i)
        send_msg( i.value(),  msg);
}

void StringServer::send_private(Address address, QByteArray msg)
{
    auto it = users_.find(address);
    send_msg( it.value(),  msg);
}

void StringServer::read()
{
    QTcpSocket* tcp_socket;
    tcp_socket = static_cast<QTcpSocket*>(sender());
    while (tcp_socket->bytesAvailable() > 0)
    {
        auto it = last_msg_.find(tcp_socket);
        QByteArray text = tcp_socket->readLine();
        QByteArray old_msg = it.value() + text;
        it.value() = "";
        Address address(tcp_socket->peerAddress(), tcp_socket->peerPort());
        if (old_msg[old_msg.size() -1] == '\n')
            emit ready_msg(old_msg, address);
        else
            last_msg_.insert(tcp_socket, old_msg);

    }
}

void StringServer::send_msg(QTcpSocket* tcp_socket, QByteArray msg)
{
    QTextStream stream(tcp_socket);
    stream.setCodec("UTF-8");
    stream << msg << "\n";
}
