#include "mainwindow.h"
#include "clientwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QApplication>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->button_quit, SIGNAL(clicked()), SLOT(close()));
  connect(ui->button_entry, SIGNAL(clicked()), SLOT(entry_chat()));
}

MainWindow::~MainWindow()
{
  delete ui;
}
// First type message - input message client
// Second type message - show online users
void MainWindow::entry_chat()
{
  QByteArray  arr_block;
  QDataStream out(&arr_block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << FIRST_TYPE << quint16(0) << ui->in_text->text();
  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  close();
  ClientWindow *client = new ClientWindow(arr_block,"localhost", 3425);
  client->show();
}



