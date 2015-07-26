#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QColor>
#include <cmath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , width_(640)
    , height_(600)
    , depth_(200)
    , light_dir_(1, 0, 0)
{
    ui->setupUi(this);
    image_ = new QImage(width_, height_, QImage::Format_RGB888);
    image_->fill(QColor(Qt::black).rgb());
    ui->label->setPixmap(QPixmap::fromImage(*image_,Qt::AutoColor));

    DataModel dataModel;
    dataModel.read_date();
    faces_ = dataModel.faces();
    verts_ = dataModel.verts() ;
    vt_ = dataModel.vt();
    vn_ = dataModel.vn();
    QImage *img = new QImage;
    img->load("pic.png");
    texture_ = img->mirrored();
    img->load("nm_pic.png");
    nm_texture_ = img->mirrored();
    img->load("african_head.obj.spec.png");
    spec_texture_ = img->mirrored();

    draw_face();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_face()
{
    int *zbuffer = new int[width_*height_];
    for (size_t i=0; i<width_*height_; ++i)
        zbuffer[i] = std::numeric_limits<int>::min();

    for (size_t i = 0; i < faces_.size(); ++i)
    {
        QVector<point_3i> triangle3D = faces_[i];

        point_3i screen_coords[3];
        point_2i tex_coords[3];
        Matrix m;

        for (int j = 0; j < 3; ++j)
        {
            point_3f verts_triangle = verts_[triangle3D[j].x];

            point_2f vt_triangle = vt_[faces_[i][j].y];
            screen_coords[j] = m.transform((verts_triangle.x+1.)*width_/2., (verts_triangle.y+1.)*height_/2., (verts_triangle.z + 1.)* depth_/2.);
            //screen_coords[j] = point_3i((verts_triangle.x+1.)*width_/2., (verts_triangle.y+1.)*height_/2., (verts_triangle.z + 1.)* depth_/2.);
            tex_coords[j] = point_2i(vt_triangle.x * texture_.width(), vt_triangle.y * texture_.height());

        }
            triagle(screen_coords, zbuffer, tex_coords);
    }
    ui->label->setPixmap(QPixmap::fromImage(image_->mirrored(),Qt::AutoColor));
}

void MainWindow::triagle(point_3i screen_coords[], int *zbuffer, point_2i tex_coords[])
{
    point_3i t0, t1, t2;
    t0 = screen_coords[0];
    t1 = screen_coords[1];
    t2 = screen_coords[2];
    point_2i uv0, uv1, uv2;
    uv0 = tex_coords[0];
    uv1 = tex_coords[1];
    uv2 = tex_coords[2];
    if (t0.y==t1.y && t0.y==t2.y) return;
    if (t0.y > t1.y)
    {
        std::swap(t0, t1);
        std::swap(uv0, uv1);
    }
    if (t0.y > t2.y)
    {
        std::swap(t0, t2);
        std::swap(uv0, uv2);
    }
    if (t1.y > t2.y)
    {
        std::swap(t1, t2);
        std::swap(uv1, uv2);
    }

    int total_height = t2.y - t0.y;
    for (int i = 0; i < total_height; ++i)
    {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        float alpha = (float)i/total_height;
        float betta  = (float)(i-(second_half ? t1.y - t0.y : 0))/segment_height;

        point_3i A = t0 + (t2 - t0) * alpha;
        point_3i B = second_half ? t1 + (t2 - t1) * betta : t0 + (t1 - t0)*betta;
        point_2i uvA = uv0 + (uv2 - uv0) * alpha;
        point_2i uvB = second_half ? uv1 + (uv2 - uv1) * betta : uv0 + (uv1 - uv0)*betta;
        if (A.x > B.x)
        {
            std::swap(A, B);
            std::swap(uvA, uvB);
        }

        for (int j = A.x; j <= B.x; ++j)
        {
            float t = B.x==A.x ? 1. :  (float)(j - A.x)/(float)(B.x - A.x);
            point_3i P = point_3i(A) + point_3f(B-A)*t;
            point_2i uvP = point_2i(uvA) + point_2i(uvB-uvA)*t;
            int idx = P.x + P.y * width_;
            if (zbuffer[idx] < P.z)
            {
                QRgb norm_col = nm_texture_.pixel(uvP.x, uvP.y);
                point_3f norm(qRed(norm_col), qGreen(norm_col), qBlue(norm_col));
                norm.normalize();
                float intensity = norm*light_dir_;
                zbuffer[idx] = P.z;
                norm_col = texture_.pixel(uvP.x, uvP.y);
                image_->setPixel(P.x, P.y, qRgb(intensity*qRed(norm_col), intensity*qGreen(norm_col), intensity*qBlue(norm_col)));
            }
        }
    }
}

void MainWindow::line(int x0, int y0, int x1, int y1, int r, int g, int b)
{
    double leight = 1/sqrt(pow(x1-x0, 2)+pow(y1-y0, 2));

    for (float t = 0; t < 1; t += leight)
    {
        int x = x0 + t * (x1 - x0);
        int y = y0 + t * (y1 - y0);
        image_->setPixel(x, y, qRgb(r, g, b));
    }
}
