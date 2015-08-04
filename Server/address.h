#pragma once
#include <QObject>
#include <QHostAddress>

class Address
{
public:
    Address();
    Address(QHostAddress IP, quint16 port);
    QHostAddress IP_;
    quint16 port_;
};

bool operator<(const Address &key1, const Address &key2);
