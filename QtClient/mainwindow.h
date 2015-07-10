#pragma once
#include "stringclient.h"
#include <QMainWindow>
#include "login.h"

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:
   Ui::MainWindow *ui;
   StringClient *stringClient_;
   LogIn *login_;

private slots:
   void entry_chat(const QString &message);
   void read_message(QString str);
   void send_message();
   void show_online(rapidjson::Document const & doc);
};

