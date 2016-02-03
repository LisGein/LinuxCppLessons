#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   QMap<int, QString> map{{1,"asd"}, {2, "fwf"}, {3, "fwf"}};
   qDebug()  << map.size() << map;
   map.remove(1);
   qDebug() << map[1]  << map.size() << map;
   map.erase(map.end() - 1);
   qDebug() << map[3] << map.size() << map;

}

MainWindow::~MainWindow()
{
   delete ui;
}
