#include "mainwindow.h"
#include "client.h"
#include "server.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QApplication>
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
  nick_name_ = ui->in_text->text();//одни и те же первые строчки. Переделать в 3 функции,
  ui->in_text->setText("");
  close();
  Client *client = new Client(nick_name_,"localhost", 8888);
  client->show();
}
void MainWindow::create_server()
{
  nick_name_ = ui->in_text->text();
  ui->in_text->setText("");
  close();
  Server *server = new Server(nick_name_, "localhost", 8888);
  server->show();
}


