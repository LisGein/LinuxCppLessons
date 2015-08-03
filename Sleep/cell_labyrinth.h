#pragma once
#include <QPair>
#include <map>
#include <QVector>
#include <QObject>


class Cell_labyrinth
{
public:
    Cell_labyrinth();
    Cell_labyrinth(QPair<int, int> coor, QPair<char, int> value_color);

    QString get_mark();
    QSet<int> get_colors();
    QPair<int, int> get_coordinates();
    bool change_colors(QSet<int> current_colors);
    QChar get_value();
    bool change();

private:
    QPair<int, int> coordinates_;
    QChar value_;
    //QSet <int> colors_;
    int start_colors_;
    bool change_;
};
