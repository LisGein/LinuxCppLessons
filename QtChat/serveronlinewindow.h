#pragma once
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QTcpSocket>

class ServerOnlineWindow: public QWidget {
  Q_OBJECT
public:
  ServerOnlineWindow(QWidget *pwgt = 0);

private:
  QMap<QString, QTcpSocket*> connected_users_port_;
  QListWidget* out_online_;
  QVBoxLayout* window_online_layout_;

signals:
  void signal_show_online();
  void signal_del_user(QTcpSocket*);
  void signal_refresh_online();
  void signal_close();

public slots:
  void slot_show_online(QMap<QString, QTcpSocket *> connected_users_port);
  void slot_refresh(QMap<QString, QTcpSocket*> connected_users_port);
  void slot_delete_user(QListWidgetItem* user_name);
  void slot_refreshing();
};

