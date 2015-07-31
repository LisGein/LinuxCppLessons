#pragma once
#include <QPair>
#include <QMap>
#include <QVector>
#include <QObject>
#include "cell_labyrinth.h"

class Labyrinth
{
public:
    Labyrinth(int width_labirinth, int height_labirinth);
    void add_element(Cell_labyrinth cell);
    QVector<int> find_way();

private:
   int width_;
   int height_;
   QVector<Cell_labyrinth> cells_;

};

