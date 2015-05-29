#include "listonlineclient.h"
#include "ui_listonlineclient.h"
#include <QPushButton>

ListOnlineClient::ListOnlineClient(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ListOnlineClient)
{
  ui->setupUi(this);
}

ListOnlineClient::~ListOnlineClient()
{
  delete ui;
}
void ListOnlineClient::slot_refresh(QString connected_users_port)
{
  ui->textEdit->clear();
  ui->textEdit->setReadOnly(true);
  ui->textEdit->setText(connected_users_port);
}

