#pragma once
#include "cell_labyrinth.h"
#include <QDialog>
#include <QByteArray>
#include <QMap>

namespace Ui {
class DataAlternativeReality;
}

class DataAlternativeReality : public QDialog
{
    Q_OBJECT

public:
    explicit DataAlternativeReality(QWidget *parent = 0);
    ~DataAlternativeReality();
    void calc_labyrinth();
    void calc_prev_cell();
    QVector<Cell_labyrinth> get_labyrinth();
    Cell_labyrinth get_prev_cell();
    int convert_price(int bitset);

private slots:
    void check_data();

private:
    Ui::DataAlternativeReality *ui;
    int width_;
    int height_;
    int r_price_, g_price_, b_price_, y_price_;
    std::string description_;
    QVector<Cell_labyrinth> labyrinth_;
    Cell_labyrinth prev_cell_;

signals:
    void ready_reality(int width, int height, int R, int G, int B, int Y);
    void error_input(QString error_var);
};
