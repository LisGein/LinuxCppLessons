#include "registration.h"
#include "ui_registration.h"
#include <QDebug>

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(regs()));
}

Registration::~Registration()
{
    delete ui;
}

void Registration::regs()
{
    QString nick = ui->in_text->text();
    QString IP = ui->IPEdit->text();
    emit login(nick, IP);
    qobject_cast<QDialog *>(parent())->accept();

}
