#pragma once
#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QVector>
#include <utility>
#include "point_t.h"
#include <QImage>


typedef QVector<point_3i> vector_3i;

class DataModel
{
public:
    DataModel();
    void read_date();
    QVector<vector_3i> faces();
    QVector<point_3f> verts();
    QVector<point_2f> vt();
    QVector<point_3f> vn();

private:
    QVector<point_3f> verts_;
    QVector<vector_3i > faces_;
    QVector<point_3f> vn_;
    QVector<point_2f> vt_;
};

