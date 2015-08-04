#include "address.h"

Address::Address()
{

}

Address::Address(QHostAddress IP, quint16 port)
    :IP_(IP)
    , port_(port)
{

}

bool operator<(const Address &key1, const Address &key2)
{
    QString key1_IP = key1.IP_.toString();
    quint16 key1_port = key1.port_;
    QString key2_IP = key2.IP_.toString();
    quint16 key2_port = key2.port_;
    int compare_IP = QString::compare(key1_IP, key2_IP);
    if (compare_IP > 0)
        return true;
    else if (compare_IP < 0)
        return false;
    else if (key1_port < key2_port)
        return true;
    else if (key1_port > key2_port)
        return false;
    else
        return false;
}
