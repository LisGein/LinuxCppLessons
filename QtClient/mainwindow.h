#pragma once
#include "stringclient.h"
#include <QMainWindow>
#include "registration.h"
#include <QListWidgetItem>

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
   Registration *registration_;

private slots:
   void read_message(QString str);
   void send_message();
   void show_online(rapidjson::Document const & doc);
   void create_private(QListWidgetItem* select_user);
};

