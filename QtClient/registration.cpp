#include "registration.h"
#include "ui_registration.h"

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
    QString message = ui->in_text->text();
    emit login(message);
    qobject_cast<QDialog *>(parent())->accept();
}
