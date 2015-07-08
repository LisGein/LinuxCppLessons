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
    rapidjson::Value msg_value;
    msg_value.SetString(msg.toUtf8().constData(), msg.toUtf8().size(), allocator);
    d.AddMember("msg", msg_value, allocator);

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
