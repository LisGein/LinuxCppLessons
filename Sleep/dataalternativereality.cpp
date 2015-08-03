#include "dataalternativereality.h"
#include "ui_dataalternativereality.h"

DataAlternativeReality::DataAlternativeReality(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataAlternativeReality)
{
    ui->setupUi(this);
    connect(ui->R, SIGNAL(selectionChanged()), ui->R, SLOT(clear()));
    connect(ui->G, SIGNAL(selectionChanged()), ui->G, SLOT(clear()));
    connect(ui->B, SIGNAL(selectionChanged()), ui->B, SLOT(clear()));
    connect(ui->Y, SIGNAL(selectionChanged()), ui->Y, SLOT(clear()));
    connect(ui->height, SIGNAL(selectionChanged()), ui->height, SLOT(clear()));
    connect(ui->wigth, SIGNAL(selectionChanged()), ui->wigth, SLOT(clear()));
    connect(ui->description, SIGNAL(selectionChanged()), ui->description, SLOT(clear()));
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(check_data()));
}

DataAlternativeReality::~DataAlternativeReality()
{
    delete ui;
}
void DataAlternativeReality::check_data()
{
    QString error_var;

    width_ = ui->wigth->toPlainText().toInt();
    height_ = ui->height->toPlainText().toInt();

    QString read_data = ui->description->toPlainText();
    read_data.replace("\n", "");
    description_ = read_data.toStdString();

    if (read_data.size() != (width_*height_))//||(description.size() > (width*height + height)))
        error_var = "description";
    else if ((read_data.count("S") != 1) || (read_data.count("E") != 1))
        error_var = "description";

    if ((width_ > 50)||(height_ > 50))
        if (error_var.size() != 0)
            error_var += ", width or height";
        else
            error_var = "width or height";

    r_price_ = ui->R->toPlainText().toInt();
    g_price_ = ui->G->toPlainText().toInt();
    b_price_ = ui->B->toPlainText().toInt();
    y_price_ = ui->Y->toPlainText().toInt();
    if ((r_price_ > 100)||(g_price_ > 100)||(b_price_ > 100)||(y_price_ > 100))
        if (error_var.size() != 0)
            error_var += ", price";
        else
            error_var = "price";

    if (error_var.size() == 0)
        emit ready_reality(width_, height_, r_price_, g_price_, b_price_, y_price_);
    else
        emit error_input(error_var);
}

void DataAlternativeReality::calc_labyrinth()
{
    QMap<char, int> const color2flag {
        { 'r', 0b1000 },
        { 'g', 0b0100 },
        { 'b', 0b0010 },
        { 'y', 0b0001 },
    };
    for (size_t i = 0; i < description_.size(); ++i)
    {
        size_t x = (i >= width_) ? (i%width_) : (i);
        size_t y = (i >= width_) ? (i/width_) : (0);
        auto cell_color = color2flag.find(description_[i]);
        QPair<int, int> coor(x, y);
        if (cell_color != color2flag.end())
        {
            QPair<char, int> value_color(cell_color.key(), cell_color.value());
            labyrinth_.push_back(Cell_labyrinth(coor, value_color));
        }
        else
        {
            QPair<char, int> cell(description_[i], 0b0000);
            labyrinth_.push_back(Cell_labyrinth(coor, cell));
        }
    }
}

void DataAlternativeReality::calc_prev_cell()
{
    for (size_t i = 0; i < labyrinth_.size(); ++i)
        if (labyrinth_[i].get_value() == 's')
            prev_cell_ = labyrinth_[i];
}

QVector<Cell_labyrinth> DataAlternativeReality::get_labyrinth()
{
    return labyrinth_;
}

Cell_labyrinth DataAlternativeReality::get_prev_cell()
{
    return prev_cell_;
}

int DataAlternativeReality::convert_price(int bitset)
{
    QVector <int> result;
    int next = bitset;
    while (next != 0)
    {
        result.push_back(next % 2);
        next = next / 2;
    }
    int result_bitset = 0;
    int idx = 1;
    for (size_t i = 0; i < result.size(); ++i)
    {
        result_bitset +=  result[i] * idx;
        idx *= 10;
    }
    return result_bitset;
}

