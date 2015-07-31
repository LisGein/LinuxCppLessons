#pragma once
#include <QPair>
#include <QMap>
#include <QVector>
#include <QObject>


class Cell_labyrinth
{
public:
    Cell_labyrinth();
    Cell_labyrinth(int width_labirinth, int height_labirinth, QPair<int, int> coor, QString value_coil);

    QString get_mark();
    QVector<int> get_colors();
    QPair<int, int> get_coordinates();
    int change_color(QVector<int> current_color);


private:
    QPair<int, int> coordinates_;
    QString value_coil_;
    int width_;
    int height_;
    QVector<int> colors_;
};
