#include "listonline.h"
#include "ui_listonline.h"
#include <QPushButton>

ListOnline::ListOnline(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ListOnline)
{
  ui->setupUi(this);

}

ListOnline::~ListOnline()
{
  delete ui;
}

void ListOnline::slot_refresh(QMap<QString, QTcpSocket*> connected_users_port)
{
  for (auto it_users_port = connected_users_port_.begin(); it_users_port != connected_users_port_.end(); ++it_users_port)
    {
      QListWidgetItem *online_user = new QListWidgetItem;
      online_user->setText(it_users_port.key());
      ui->listWidget->removeItemWidget(online_user);
    }
  connected_users_port_ = connected_users_port;
  int pos = 0;
  ui->listWidget->clear();
  for (auto it_users_port = connected_users_port_.begin(); it_users_port != connected_users_port_.end(); ++it_users_port)
    {
      QListWidgetItem *online_user = new QListWidgetItem;
      online_user->setText(it_users_port.key());
      ui->listWidget->insertItem(pos, online_user);
      pos++;
      connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slot_delete_user(QListWidgetItem*)));
    }
}

void ListOnline::slot_delete_user(QListWidgetItem* user_name)
{
  if(user_name != prev_user_name)
    {
      QString nick_name = user_name->text();
      auto del_user = connected_users_port_.find(nick_name);
      emit signal_del_user(del_user.value());
      prev_user_name = user_name;
    }
}


