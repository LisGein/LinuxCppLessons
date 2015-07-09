#include "listonline.h"
#include "ui_listonline.h"

ListOnline::ListOnline(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListOnline)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

ListOnline::~ListOnline()
{
    delete ui;
}

void ListOnline::out_users(QVector<QString> const& list_online_users)
{
    for (size_t i = 0; i < list_online_users.size(); ++i)
        ui->textEdit->append(list_online_users[i]);
}
