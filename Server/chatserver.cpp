#include "chatserver.h"
#include "stringserver.h"
#include <QMap>
#include <QIODevice>


ChatServer::ChatServer(int port, QObject *parent)
    : tcp_server_(new QTcpServer(this))
    , udpSocket_(new QUdpSocket(this))
{
    stringServer_ = new StringServer(port);
    connect(stringServer_, SIGNAL(ready_msg(QByteArray, Address)), this, SLOT(read_in_data(QByteArray, Address)));
    connect(stringServer_, SIGNAL(delete_user(Address)), this, SLOT(delete_user(Address)));
    message_processors_map_["msg"] = std::bind(&ChatServer::process_msg, this, std::placeholders::_3);
    message_processors_map_["register"] = std::bind(&ChatServer::reg_user, this, std::placeholders::_1, std::placeholders::_2);
    message_processors_map_["private"] = std::bind(&ChatServer::private_msg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    message_processors_map_["online"] = std::bind(&ChatServer::list_online, this);

    if (!udpSocket_->bind(QHostAddress::Any, 3425))
    {
        udpSocket_->close();
        return;
    }
    connect(udpSocket_, SIGNAL(readyRead()), SLOT(broadcast_audio()));


}

ChatServer::~ChatServer()
{
}

void ChatServer::broadcast_audio()
{
    while (udpSocket_->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udpSocket_->pendingDatagramSize());
        udpSocket_->readDatagram(data.data(), data.size());
        for (int i = 0; i < users_address_.size(); ++i)
        {
            udpSocket_->writeDatagram(data, data.size(),users_address_[i]->peerAddress(), users_address_[i]->peerPort());
        }
    }
}

void ChatServer::list_online()
{
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("type", "online_users", allocator);
    rapidjson::Value msg_key;
    msg_key.SetArray();
    for (auto it = users_.begin(); it != users_.end(); ++it)
    {
        rapidjson::Value msg_value;
        msg_value.SetString(it.value().toUtf8().constData(), it.value().toUtf8().size(), allocator);
        msg_key.PushBack(msg_value, allocator);
    }
    d.AddMember("list", msg_key, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<> > writer(buffer);
    d.Accept(writer);

    stringServer_->send_all(buffer.GetString());
}

void ChatServer::process_msg(QByteArray message)
{
    stringServer_->send_all(message);
}

void ChatServer::private_msg(rapidjson::Document const & doc, Address host_sender, QByteArray message)
{
    QString addressee = doc["addressee"].GetString();
    auto i = re_users_.find(addressee);
    if (i != re_users_.end())
    {
        stringServer_->send_private(i.value(), message);
        stringServer_->send_private(host_sender, message);
    }
    else
    {
        QString msg_text = addressee;
        msg_text .append(" offline");
        QByteArray return_message = create_msg(msg_text);
        stringServer_->send_private(host_sender, return_message);
    }
}

void ChatServer::reg_user(rapidjson::Document const & doc, Address host_sender)
{
    QString text_message = doc["msg"].GetString();
    re_users_.insert(text_message, host_sender);
    users_.insert(host_sender, text_message);
    QUdpSocket *udp = new QUdpSocket;
    udp->connectToHost(host_sender.IP_, 3325);

    connect(udp, SIGNAL(readyRead()), SLOT(broadcast_audio()));
    users_address_.push_back(udp);

    text_message.append(" connected");
    QByteArray return_message = create_msg(text_message);
    stringServer_->send_all(return_message);
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("type", "online_users", allocator);
    rapidjson::Value msg_key;
    msg_key.SetArray();
    for (auto it = users_.begin(); it != users_.end(); ++it)
    {
        rapidjson::Value msg_value;
        msg_value.SetString(it.value().toUtf8().constData(), it.value().toUtf8().size(), allocator);
        msg_key.PushBack(msg_value, allocator);
    }
    d.AddMember("list", msg_key, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<> > writer(buffer);
    d.Accept(writer);
    stringServer_->send_all(buffer.GetString());

}

void ChatServer::delete_user(Address host_sender)//ToDo del in users_address
{
    auto it = users_.find(host_sender);
    if (it != users_.end())
    {
        QString msg_text = it.value();
        msg_text.append(" disconnected");
        QByteArray return_message = create_msg(msg_text);

        stringServer_->send_all(return_message);

        re_users_.remove(it.value());
        users_.remove(it.key());
        //users_address_.erase(it.key());
    }
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("type", "online_users", allocator);
    rapidjson::Value msg_key;
    msg_key.SetArray();
    for (auto it = users_.begin(); it != users_.end(); ++it)
    {
        rapidjson::Value msg_value;
        msg_value.SetString(it.value().toUtf8().constData(), it.value().toUtf8().size(), allocator);
        msg_key.PushBack(msg_value, allocator);
    }
    d.AddMember("list", msg_key, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<> > writer(buffer);
    d.Accept(writer);
    stringServer_->send_all(buffer.GetString());
}

void ChatServer::read_in_data(QByteArray message, Address host_sender)
{
    rapidjson::Document doc;
    doc.Parse(message);
    bool fail_parse = doc.HasParseError();
    if (fail_parse)
        error_parse_msg();
    else
    {
        QString type = doc["type"].GetString();
        if (message_processors_map_.contains(type))
            message_processors_map_[type](doc, host_sender, message);
        else
            error_parse_msg();
    }
}

void ChatServer::error_parse_msg()
{
    qDebug() << "error parse message";
}

QByteArray ChatServer::create_msg(QString const& msg)
{
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    rapidjson::Value msg_value;
    msg_value.SetString(msg.toUtf8().constData(), msg.toUtf8().size(), allocator);
    d.AddMember("name", "info message", allocator);
    d.AddMember("type", "msg", allocator);
    d.AddMember("msg", msg_value, allocator);
    d.AddMember("addressee", " - ", allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<> > writer(buffer);
    d.Accept(writer);

    return buffer.GetString();
}

