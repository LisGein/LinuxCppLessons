#pragma once
#include "guiclient.h"
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
   GuiClient* client_;

private slots:
   void entry_chat();
};

