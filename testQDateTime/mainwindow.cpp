#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QDateTime q = QDateTime::currentDateTime();
   int i = 1;
   while (q.date().year() != 2300)
   {
      q = q.addYears(i);
      qDebug() << q.toString();
   }
}

MainWindow::~MainWindow()
{
   delete ui;
}
