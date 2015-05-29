#pragma once
#include <QWidget>

namespace Ui {
  class ListOnlineClient;
}

class ListOnlineClient : public QWidget
{
  Q_OBJECT

public:
  explicit ListOnlineClient(QWidget *parent = 0);
  ~ListOnlineClient();

private:
  Ui::ListOnlineClient *ui;

private slots:
  void slot_refresh(QString connected_users_port);
};

