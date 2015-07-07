#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::entry_chat()
{
   QString nick = ui->in_text->text();
   QByteArray cd_nick;
   cd_nick.append(nick);
   client_ = new GuiClient(cd_nick, 3425, "109.234.35.126");
   client_->show();
   this->close();
}
