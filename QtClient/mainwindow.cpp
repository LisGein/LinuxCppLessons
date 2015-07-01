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
   client_ = new GuiClient(ui->in_text->text(), 3425, "localhost");
   client_->show();
   this->close();
}
