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
    connect(alt_reality_, SIGNAL(ready_reality(int, int, int, int, int, int)), SLOT(start_sleep(int, int, int, int, int, int)));
    connect(alt_reality_, SIGNAL(error_input(QString)), SLOT(message_error(QString)));
    alt_reality_->exec();
    connect(ui->close, SIGNAL(clicked(bool)), SLOT(close()));
    connect(ui->restart, SIGNAL(clicked(bool)), SLOT(restart_input()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::draw_color(QRgb color, QPair<int, int> current_coor)
{
    int x = current_coor.first * INCREASE;
    int y = current_coor.second * INCREASE;
    for (int j = 0; j < INCREASE; ++j)
        for (int i = 0; i < INCREASE; ++i)
            labyrinth_img_->setPixel(x + j, y + i, color);
}



void MainWindow::write_data(Cell_labyrinth& exit)
{
    if (exit.change())
    {
        QSet<int> result_colors = exit.get_colors();
        QSet<int> result;

        for (auto idx = result_colors.begin(); idx != result_colors.end(); ++idx)
        {
            int convert = alt_reality_->convert_price(*idx);
            int r = ((convert)/1000 * r_price_);
            int g  = ((convert)/100 % 10 * g_price_);
            int b = (((convert)/10) % 10)* b_price_;
            int y = ((convert)%10) * y_price_;
            result.insert(r + g + b + y);
        }
        ui->textEdit->setText(QString::number(*result.begin()));
    }
    else
        ui->textEdit->setText("Sleep\n");
}

void MainWindow::start_sleep(int width, int height, int R, int G, int B, int Y)
{
    width_ = width;
    height_ = height;
    labyrinth_img_ = new QImage(width_*INCREASE , height_*INCREASE, QImage::Format_RGB888);
    labyrinth_img_->fill(QColor(Qt::white).rgb());
    alt_reality_->calc_labyrinth();
    alt_reality_->calc_prev_cell();
    r_price_ = R;
    g_price_ = G;
    b_price_ = B ;
    y_price_ = Y;
    QVector<Cell_labyrinth> labyrinth = alt_reality_->get_labyrinth();
    QVector<Cell_labyrinth> prev_cell;
    prev_cell.push_back(alt_reality_->get_prev_cell());

    while (!prev_cell.empty())
    {
        QVector<Cell_labyrinth> next_cell;
        for (size_t i = 0; i < prev_cell.size(); ++i)
        {
            QPair<int, int> curr_coor = prev_cell[i].get_coordinates();
            for (size_t j = 0; j < labyrinth.size(); ++j)
            {

                std::pair<int, int> diff_coor(labyrinth[j].get_coordinates().first - curr_coor.first,
                                              labyrinth[j].get_coordinates().second - curr_coor.second);
                if (((abs(diff_coor.first) + abs (diff_coor.second)) == 1)
                        && (labyrinth[j].change_colors(prev_cell[i].get_colors())))
                {
                    next_cell.push_back(labyrinth[j]);
                }
            }

        }

        prev_cell = next_cell;
    }

    Cell_labyrinth exit;
    for (size_t i = 0; i < labyrinth.size(); ++i)
        if (labyrinth[i].get_value() == 'e')
            exit = labyrinth[i];
    write_data(exit);

    ui->label->setPixmap(QPixmap::fromImage(*labyrinth_img_,Qt::AutoColor));
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
