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
    QByteArray byte_msg;
    byte_msg.append(msg);     
    if (byte_msg[0] == '@')
    {
        int pos = msg.indexOf(' ');
        QString nick = msg;
        nick.remove(0,1);
        nick.resize(pos-1);
        byte_msg.remove(0, pos);
        QMap<QString, QString> message;
        message.insert("name", nick_user_ + "(private)");
        message.insert("type", "private");
        message.insert("msg", byte_msg);
        message.insert("addressee", nick);
        generete_doc(message);
    }
    else
    {
        QMap<QString, QString> message;
        message.insert("name", nick_user_);
        message.insert("type", "msg");
        message.insert("msg", msg);
        message.insert("addressee", "");
        generete_doc(message);
    }
}

void StringClient::read()
{
    while (tcp_socket_->bytesAvailable() > 0)
    {
        last_msg_ += tcp_socket_->readLine();
        if ((last_msg_.size() > 2)&&(last_msg_[last_msg_.size() -1] == '\n')) // last_msg_.size() > 2 because sizeof("{}") == 2
        {
            QByteArray array_msg;
            array_msg.append(last_msg_);
            rapidjson::Document doc;
            doc.Parse(array_msg);
            bool fail_parse = doc.HasParseError();
            if (fail_parse)
                qDebug() << "error parse message";
            else
            {
                QString type = doc["type"].GetString();
                if (type == "online_users")
                    emit ready_online(doc);
                else if (type == "private")
                {
                    QString name = doc["name"].GetString();
                    qDebug() << name;
                    emit ready_msg(last_msg_);
                }
                else
                    emit ready_msg(last_msg_);
                last_msg_ = "";
            }
        }
    }
}

void StringClient::login(QString const& msg)
{
    nick_user_ = msg;
    QMap<QString, QString> message;
    message.insert("name", nick_user_);
    message.insert("type", "register");
    message.insert("msg", msg);
    message.insert("addressee", "");
    generete_doc(message);
}

void StringClient::request_list_online()
{
    QMap<QString, QString> message;
    message.insert("name", nick_user_);
    message.insert("type", "online");
    message.insert("msg", "");
    message.insert("addressee", "");
    generete_doc(message);
}

void StringClient::generete_doc(QMap<QString, QString> message)
{
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    auto name = message.find("name");
    rapidjson::Value name_value;
    name_value.SetString(name.value().toUtf8().constData(), name.value().toUtf8().size(), allocator);
    d.AddMember("name", name_value, allocator);

    auto type = message.find("type");
    rapidjson::Value type_value;
    type_value.SetString(type.value().toUtf8().constData(), type.value().toUtf8().size(), allocator);
    d.AddMember("type", type_value, allocator);

    auto msg = message.find("msg");
    rapidjson::Value msg_value;
    msg_value.SetString(msg.value().toUtf8().constData(), msg.value().toUtf8().size(), allocator);
    d.AddMember("msg", msg_value, allocator);

    auto addressee = message.find("addressee");
    rapidjson::Value addressee_value;
    addressee_value.SetString(addressee.value().toUtf8().constData(), addressee.value().toUtf8().size(), allocator);
    d.AddMember("addressee", addressee_value, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<> > writer(buffer);
    d.Accept(writer);
    tcp_socket_->write(buffer.GetString());
    tcp_socket_->write("\n");
}
