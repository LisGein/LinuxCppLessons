#include "serveronlinewindow.h"
#include <QPushButton>

ServerOnlineWindow::ServerOnlineWindow(QWidget* pwgt)
  : QWidget(pwgt)
{
}

void ServerOnlineWindow::slot_show_online(QMap<QString, QTcpSocket *> connected_users_port)
{
  window_online_layout_ = new QVBoxLayout;
  out_online_ = new QListWidget;
  connected_users_port_ = connected_users_port;
  int pos = 0;
  for (auto it_users_port = connected_users_port_.begin(); it_users_port != connected_users_port_.end(); ++it_users_port)
    {
      QListWidgetItem *online_user = new QListWidgetItem;
      online_user->setText(it_users_port.key());
      out_online_->insertItem(pos, online_user);
      pos++;
      connect(out_online_, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slot_delete_user(QListWidgetItem*)));
    }
  window_online_layout_->addWidget(out_online_);
  this->setWindowTitle("Online users");
  this->setLayout(window_online_layout_);
  this->show();
}

void ServerOnlineWindow::slot_refresh(QMap<QString, QTcpSocket*> connected_users_port)
{
  for (auto it_users_port = connected_users_port_.begin(); it_users_port != connected_users_port_.end(); ++it_users_port)
    {
      QListWidgetItem *online_user = new QListWidgetItem;
      online_user->setText(it_users_port.key());
      out_online_->removeItemWidget(online_user);
    }
  window_online_layout_->removeWidget(out_online_);
  connected_users_port_ = connected_users_port;
  int pos = 0;
  out_online_ = new QListWidget;
  for (auto it_users_port = connected_users_port_.begin(); it_users_port != connected_users_port_.end(); ++it_users_port)
    {
      QListWidgetItem *online_user = new QListWidgetItem;
      online_user->setText(it_users_port.key());
      out_online_->insertItem(pos, online_user);
      pos++;
      connect(out_online_, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slot_delete_user(QListWidgetItem*)));
    }
  window_online_layout_->addWidget(out_online_);
}

void ServerOnlineWindow::slot_delete_user(QListWidgetItem* user_name)
{
  auto del_user = connected_users_port_.find(user_name->text());
  emit signal_del_user(del_user.value());
}

void ServerOnlineWindow::slot_refreshing()
{
  emit signal_refresh_online();
}
