#pragma once

#include <QWidget>

namespace Ui {
class ListOnline;
}

class ListOnline : public QWidget
{
    Q_OBJECT

public:
    explicit ListOnline(QWidget *parent = 0);
    ~ListOnline();

    void out_users(const QVector<QString> &users);

private:
    Ui::ListOnline *ui;
};

