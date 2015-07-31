#include "mainwindow.h"
#include "ui_mainwindow.h"

const int INCREASE = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pos_(0)
{
    ui->setupUi(this);
    alt_reality_ = new DataAlternativeReality;
    connect(alt_reality_, SIGNAL(ready_reality(int, int, int, int, int, int, QString)), SLOT(start_sleep(int, int, int, int, int, int, QString)));
    connect(alt_reality_, SIGNAL(error_input(QString)), SLOT(message_error(QString)));
    alt_reality_->exec();
    connect(ui->close, SIGNAL(clicked(bool)), SLOT(close()));
    connect(ui->restart, SIGNAL(clicked(bool)), SLOT(restart_input()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QPair<int, int> MainWindow::calc_coor()
{
    int x = (pos_ >= width_) ? (pos_%width_) : (pos_ );
    int y = (pos_ >= width_) ? (pos_/width_) : (0);
    QPair<int, int> current_coor(x, y);
    return current_coor;
}


void MainWindow::draw_color(QRgb color, QPair<int, int> current_coor)
{
    int x = current_coor.first * INCREASE;
    int y = current_coor.second * INCREASE;
    for (int j = 0; j < INCREASE; ++j)
        for (int i = 0; i < INCREASE; ++i)
            labyrinth_img_->setPixel(x + j, y + i, color);
}

int MainWindow::calc_free_road(int R, int G, int B, int Y)
{

    QVector<int> price = labyrinth_->find_way();
    int size = price.size();
    int result = (price[size - 1] / 1000 * R)+(price[size - 1] / 100 * G) + (price[size - 1] / 10*B) + (price[size - 1] * Y);
    price.pop_back();
    for (int i = 0; i < size; ++i)
    {
        int next_result = (price[i] / 1000 * R)+(price[i] / 100 * G) + (price[i] / 10*B) + (price[i] * Y);
        result = result > next_result ? next_result : result;
    }
    return result;
}

void MainWindow::start_sleep(int width, int height,int R, int G, int B, int Y, QString description)
{

    width_ = width;
    height_ = height;
    labyrinth_ = new Labyrinth(width, height);
    labyrinth_img_ = new QImage(width_*INCREASE , height_*INCREASE, QImage::Format_RGB888);
    labyrinth_img_->fill(QColor(Qt::white).rgb());
    for (auto i = description.begin(); i != description.end(); ++i)
    {
        QPair<int, int> current_coor = calc_coor();
        QString mark;
        Cell_labyrinth *cell;
        if (*i == 'x')
        {
            draw_color(qRgb(0,0,0), current_coor);
            mark = 'x';
        }
        else if (*i == 'r')
        {
            draw_color(qRgb(255,0,0), current_coor);
            mark = 'r';
        }
        else if (*i == 'g')
        {
            draw_color(qRgb(0,255,0), current_coor);
            mark = 'g';
        }
        else if (*i == 'b')
        {
            draw_color(qRgb(0, 0, 255), current_coor);
            mark = 'b';
        }
        else if (*i == 'y')
        {
            draw_color(qRgb(150, 150,10), current_coor);
            mark = 'y';
        }
        else if (*i == 's')
        {
            draw_color(qRgb(128,128,128), current_coor);
            mark = 's';
        }
        else if (*i == 'e')
        {
            draw_color(qRgb(128, 0,128), current_coor);
            mark = 'e';
        }
        else
            mark = 'o';

        cell = new Cell_labyrinth( width, height, current_coor,  mark);
        labyrinth_->add_element(*cell);
        ++pos_;
    }

    ui->label->setPixmap(QPixmap::fromImage(*labyrinth_img_,Qt::AutoColor));
    int free_price = calc_free_road( R,  G,  B,  Y);
    ui->textEdit->setText(QString::number(free_price));
    pos_ = 0;
}

void MainWindow::message_error(QString error_var)
{
    ui->textEdit->setText("Error input " + error_var);
}

void MainWindow::restart_input()
{
    alt_reality_ = new DataAlternativeReality;
    connect(alt_reality_, SIGNAL(ready_reality(int, int, int, int, int, int, QByteArray)), SLOT(start_sleep(int, int, int, int, int, int, QByteArray)));
    connect(alt_reality_, SIGNAL(error_input(QString)), SLOT(message_error(QString)));
    alt_reality_->exec();
}
