#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPalette palette;
   palette.setColor(QPalette::Background, Qt::white);
   ui->label->setAutoFillBackground(true); //  !!!
   ui->label->setPalette(palette);
}

MainWindow::~MainWindow()
{
   delete ui;
}
