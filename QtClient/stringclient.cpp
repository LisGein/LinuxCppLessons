#include "stringclient.h"
#include <QHostAddress>

StringClient::StringClient(int port, QObject *parent)
    : last_msg_("")
    , tcp_socket_(new QTcpSocket(this))
{
    tcp_socket_->connectToHost("localhost", port);
    connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(read()));
}

StringClient::~StringClient()
{

}

void StringClient::send(QString const& msg)
{
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    QByteArray byte_msg;
    byte_msg.append(msg);
    if (byte_msg[0] == '@')
    {
        int pos = msg.indexOf(' ');
        QString nick= msg;
        nick.remove(0,1);
        nick.resize(pos-1);
        rapidjson::Value addressee;
        addressee.SetString(nick.toUtf8().constData(), nick.toUtf8().size(), allocator);
        d.AddMember("addressee", addressee, allocator);
        rapidjson::Value msg_value;
        msg_value.SetString(msg.toUtf8().constData(), msg.toUtf8().size(), allocator);
        d.AddMember("msg", msg_value, allocator);
        d.AddMember("type", "private", allocator);
    }
    else
    {
        rapidjson::Value msg_value;
        msg_value.SetString(msg.toUtf8().constData(), msg.toUtf8().size(), allocator);
        d.AddMember("msg", msg_value, allocator);
        d.AddMember("type", "msg", allocator);
    }


    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<> > writer(buffer);
    d.Accept(writer);

    tcp_socket_->write(buffer.GetString());
    tcp_socket_->write("\n");
}

void StringClient::read()
{
    while (tcp_socket_->bytesAvailable() > 0)
    {
        last_msg_ += tcp_socket_->readLine();
        if (last_msg_[last_msg_.size() -1] == '\n')
        {
            emit ready_msg(last_msg_);
            last_msg_ = "";
        }
    }
}

void StringClient::login(QString const& msg)
{
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    rapidjson::Value msg_value;
    msg_value.SetString(msg.toUtf8().constData(), msg.toUtf8().size(), allocator);
    d.AddMember("msg", msg_value, allocator);
    d.AddMember("type", "register", allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<> > writer(buffer);
    d.Accept(writer);

    tcp_socket_->write(buffer.GetString());
    tcp_socket_->write("\n");
}
