#pragma once

#include <QWidget>

namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = 0);
    ~LogIn();

private:
    Ui::LogIn *ui;

private slots:
    void register_user();

signals:
    void registration(QString const &message);
};

