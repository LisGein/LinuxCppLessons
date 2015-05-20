#pragma once
#include "servernetwork.h"
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

class QTextEdit;
class QLineEdit;

class ServerWindow: public QWidget {
  Q_OBJECT
private:
  QTextEdit*  out_text_;
  QLineEdit*  in_text_;
  QPushButton* in_cmd;
  QAction*   menu_action_;
  QMenuBar menu_bar_;
  QMenu* menu_;
  ServerNetwork *server_network_;

  void create_main_widget();
  void create_menu();
  void create_window_chat();
  void connect_signals();

public:
  ServerWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt = 0) ;

signals:
  void signal_send_server(QByteArray arrBlock);
  void signal_show_online();

public slots:
  void slot_read_in_message(QString str);
  void slot_send_to_server();
  void slot_show_online(QString online_users);
};


