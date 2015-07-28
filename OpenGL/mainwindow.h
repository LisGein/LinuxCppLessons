#pragma once
#include "matrix.h"
#include <QMainWindow>
#include <QTimer>
#include "datamodel.h"

typedef std::pair<int, int> coordinates;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void update_picture();
private:
    Ui::MainWindow *ui;
    QImage *image_;
    QImage texture_;
    QImage nm_texture_;
    QImage spec_texture_;
    QVector<vector_3i> faces_;
    QVector<point_3f> verts_;
    QVector<point_2f> vt_;
    QVector<point_3f> vn_;
    point_3f light_dir_;
    point_3f eye_;
    const point_3f center_;
    int *zbuffer_;
    QTimer *timer_;
    float angle_ ;

    void draw_face();
    void triangle(point_3i t[], point_2i uv[]);
    void set_pixel(point_3i const& P, point_2i const& uvP, int idx);
};

