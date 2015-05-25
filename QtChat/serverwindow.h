#pragma once
#include "servernetwork.h"
#include "serveronlinewindow.h"
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QListWidget>
#include <QVBoxLayout>

class QTextEdit;
class QLineEdit;

class ServerWindow: public QWidget {
  Q_OBJECT

public:
  ServerWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt = 0) ;

signals:
  void signal_send_server(QByteArray arrBlock);
  void signal_show_online();
  void signal_del_user(QTcpSocket*);
  void signal_refresh_online();

private:
  void create_main_widget();
  void create_menu();
  void create_window_chat();
  void connect_signals();

  const quint8 FIRST_TYPE = 0;
  const quint8 SECOND_TYPE = 1;
  QTextEdit*  out_text_;
  QLineEdit*  in_text_;
  QPushButton* in_cmd;
  QAction*   menu_action_;
  QMenuBar menu_bar_;
  QMenu* menu_;
  ServerNetwork *server_network_;
  ServerOnlineWindow* server_online_window_;
  QMap<QString, QTcpSocket*> connected_users_port_;
  QListWidget* out_online_;
  QVBoxLayout* window_online_layout_;

private slots:
  void slot_read_in_message(QString str);
  void slot_send_to_server();
};


