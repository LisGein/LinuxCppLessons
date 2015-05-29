#pragma once
#include <QMainWindow>

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
  QString nick_name_;
  const quint8 FIRST_TYPE = 0;
  const quint8 SECOND_TYPE = 1;

private slots:
  void entry_chat();
  void create_server();

};

