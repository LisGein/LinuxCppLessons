#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPalette palette;
   palette.setColor(QPalette::Background, Qt::white);
   ui->label->setAutoFillBackground(true); //  !!!
   ui->label->setPalette(palette);
   QImage *img = new QImage;
   img->load("/home/lisgein/Pictures/1.png");
   for(int x = 0; x < img->width(); ++x)

      img->setPixel(0, 0, qRgb(122, 163, 39));
   img->setPixel(0, 1, qRgb(122, 163, 39));
   img->setPixel(1, 0, qRgb(122, 163, 39));
   img->setPixel(1, 1, qRgb(122, 163, 39));
   img->setPixel(1, 2, qRgb(122, 163, 39));
   img->setPixel(2, 1, qRgb(122, 163, 39));
   img->setPixel(2, 2, qRgb(122, 163, 39));


   ui->label->setPixmap(QPixmap::fromImage(*img));
}

MainWindow::~MainWindow()
{
   delete ui;
}
