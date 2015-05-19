#include "mainwindow.h"
#include "clientwindow.h"
#include "serverwindow.h"
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
  connect(ui->button_server, SIGNAL(clicked()), SLOT(create_server()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::entry_chat()
{
  QByteArray  arr_block;
  QDataStream out(&arr_block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << QTime::currentTime() << ui->in_text->text();
  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  close();
  ClientWindow *client = new ClientWindow(arr_block,"localhost", 8888);
  client->show();
}
void MainWindow::create_server()
{
  QByteArray  arr_block;
  QDataStream out(&arr_block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << QTime::currentTime() << ui->in_text->text();
  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  close();
  ServerWindow *server = new ServerWindow(arr_block, "localhost", 8888);
  server->show();
}


