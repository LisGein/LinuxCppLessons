#pragma once
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QTcpSocket>

namespace Ui {
  class ListOnline;
}

class ListOnline : public QWidget
{
  Q_OBJECT

public:
  explicit ListOnline(QWidget *parent = 0);
  ~ListOnline();

private:
  Ui::ListOnline *ui;
  QMap<QString, QTcpSocket*> connected_users_port_;
  QListWidget* out_online_;
  QVBoxLayout* window_online_layout_;
  QListWidgetItem* prev_user_name;

signals:
  void signal_show_online();
  void signal_del_user(QTcpSocket*);
  void signal_refresh_online();

private slots:
  void slot_refresh(QMap<QString, QTcpSocket*> connected_users_port);
  void slot_delete_user(QListWidgetItem* user_name);

};

