#pragma once

#include <QDialog>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();

private:
    Ui::Registration *ui;

private slots:
    void regs();

signals:
    void login(QString const &message);
};
