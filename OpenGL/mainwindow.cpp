#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image_ = new QImage(640, 480, QImage::Format_RGB888);
    image_->fill(QColor(Qt::black).rgb());
    ui->label->setPixmap(QPixmap::fromImage(*image_,Qt::AutoColor));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::line(int x0, int x1, int y0, int y1)
{
    int a = x1 - x0;
    int b = y1 - y0;
    for (int x = x0; x < x1; ++x)
        for (int y = y0; y < y1; ++y)
        {
            int f = ((x - x1 / a)) - ((y - y1 / b));
            if (f == 0)
                image_->setPixel(x, y, qRgb(255, 255, 255));
        }
    ui->label->setPixmap(QPixmap::fromImage(*image_,Qt::AutoColor));
}
