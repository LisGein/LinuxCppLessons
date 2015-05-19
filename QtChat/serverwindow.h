#pragma once
#include "servernetwork.h"
#include <QWidget>
#include <QMenu>
#include <QMenuBar>

class QTextEdit;
class QLineEdit;

class ServerWindow: public QWidget {
  Q_OBJECT
private:
  QTextEdit*  out_text_;
  QLineEdit*  in_text_;
  QAction*   menu_action_;
  QMenuBar *menu_bar_;

public:
  ServerWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt = 0) ;

signals:
  void signal_send_server(QByteArray arrBlock);

public slots:
  void slot_read_in_message(QString str);
  void slot_send_to_server();
  void slot_show_menu();
};


