#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    connect(ui->log_in, SIGNAL(clicked()), SLOT(register_user()));
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::register_user()
{
    QString message = ui->in_text->text();
    emit registration(message);
}
