#include "chatserver.h"
#include "stringserver.h"


ChatServer::ChatServer(int port, QObject *parent)
    : tcp_server_(new QTcpServer(this))
{
    stringServer_ = new StringServer(port);
    connect(stringServer_, SIGNAL(ready_msg(QByteArray, QHostAddress, quint16)), this, SLOT(read_in_data(QByteArray, QHostAddress, quint16)));
    connect(stringServer_, SIGNAL(delete_user(QHostAddress, quint16)), this, SLOT(delete_user(QHostAddress, quint16)));
}

ChatServer::~ChatServer()
{
}

void ChatServer::delete_user(const QHostAddress &host_sender, quint16 port_sender)
{
    auto it = users_.find(port_sender);
    QString msg_text = it.value();
    msg_text.append(" disconnected");
    QByteArray return_message = create_msg(msg_text);

    stringServer_->send_all(return_message);
    stringServer_->send_all("\n");

    re_users_.remove(it.value());
    users_.remove(it.key());
}

void ChatServer::read_in_data(QByteArray message, const QHostAddress &host_sender, quint16 port_sender)
{
    rapidjson::Document doc;
    doc.Parse(message);
    bool fail_parse = doc.HasParseError();
    auto it = users_.find(port_sender);
    QString text_message = doc["msg"].GetString();

    if (fail_parse)
        error_parse_msg();

    else if (it != users_.end())
        if (text_message[0] == '@')
            send_private_msg(message, text_message, host_sender, port_sender);
        else
            stringServer_->send_all(message);

    else
        connect_new_user(text_message, host_sender, port_sender);

}

void ChatServer::error_parse_msg()
{
    qDebug() << "error parse message";
}

void ChatServer::send_private_msg(QByteArray const& message, QString const& msg, const QHostAddress &host_sender, quint16 port_sender)
{
    QString nick = find_receiver_nick( msg);
    auto i = re_users_.find(nick);
    if (i != re_users_.end())
    {
        stringServer_->send_private(i.value(), message);
        stringServer_->send_private(port_sender, message);
    }
    else
    {
        QString msg_text = nick;
        msg_text .append(" offline");
        QByteArray return_message = create_msg(msg_text);
        stringServer_->send_private(port_sender, return_message);
        stringServer_->send_private(port_sender, "\n");
    }
}

QByteArray ChatServer::create_msg(QString const& msg)
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

    return buffer.GetString();
}

void ChatServer::connect_new_user(QString text_message, QHostAddress const& host_sender, quint16 port_sender)
{
    re_users_.insert(text_message, port_sender);
    users_.insert(port_sender, text_message);
    text_message.append(" connected");
    QByteArray return_message = create_msg(text_message);
    stringServer_->send_all(return_message);
    stringServer_->send_all("\n");
}

QString ChatServer::find_receiver_nick(QString const& msg)
{
    int pos = msg.indexOf(' ');
    QString nick= msg;
    nick.remove(0,1);
    nick.resize(pos-1);
    return nick;
}

