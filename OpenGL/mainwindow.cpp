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
    , light_dir_(1, 0, 0)
    , eye_(5,0,1)
    , center_(1,1,1)
    , angle_(0.2)
{
    ui->setupUi(this);
    image_ = new QImage(width_, height_, QImage::Format_RGB888);
    image_->fill(QColor(Qt::black).rgb());
    ui->label->setPixmap(QPixmap::fromImage(*image_,Qt::AutoColor));
    light_dir_.normalize();

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
    timer_ = new QTimer();
    connect(timer_, SIGNAL(timeout()), this, SLOT(update_picture()));
    timer_->start(100);

    zbuffer_ = new int[width_*height_];
    for (size_t i=0; i<width_*height_; ++i)
        zbuffer_[i] = std::numeric_limits<int>::min();
    update_picture();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_picture()
{
    image_->fill(QColor(Qt::black).rgb());
    angle_ += 0.01;
    eye_.rotate_to(angle_);
    for (size_t i=0; i<width_*height_; ++i)
        zbuffer_[i] = std::numeric_limits<int>::min();
    draw_face();
}

void MainWindow::set_pixel(point_3i const& P, point_2i const& uvP, int idx)
{
    QRgb norm_col = nm_texture_.pixel(uvP.x, uvP.y);
    point_3f norm(qRed(norm_col), qGreen(norm_col), qBlue(norm_col));
    norm.normalize();
    float intensity = norm*light_dir_;
    zbuffer_[idx] = P.z;
    norm_col = texture_.pixel(uvP.x, uvP.y);
    image_->setPixel(P.x, P.y, qRgb(intensity*qRed(norm_col), intensity*qGreen(norm_col), intensity*qBlue(norm_col)));
}

void MainWindow::triangle(point_3i t[], point_2i uv[])
{
    if (t[0].y == t[1].y && t[0].y == t[2].y) return;
    if (t[0].y > t[1].y)
    {
        std::swap(t[0], t[1]);
        std::swap(uv[0], uv[1]);
    }
    if (t[0].y > t[2].y)
    {
        std::swap(t[0], t[2]);
        std::swap(uv[0], uv[2]);
    }
    if (t[1].y > t[2].y)
    {
        std::swap(t[1], t[2]);
        std::swap(uv[1], uv[2]);
    }

    int total_height = t[2].y - t[0].y;
    for (int i = 0; i < total_height; ++i)
    {
        bool second_half = i > t[1].y - t[0].y || t[1].y == t[0].y;
        int segment_height = second_half ? t[2].y - t[1].y : t[1].y - t[0].y;
        float alpha = (float)i/total_height;
        float betta  = (float)(i-(second_half ? t[1].y - t[0].y : 0))/segment_height;

        point_3i A = t[0] + (t[2] - t[0]) * alpha;
        point_3i B = second_half ? t[1] + (t[2] - t[1]) * betta : t[0] + (t[1] - t[0])*betta;
        point_2i uvA = uv[0] + (uv[2] - uv[0]) * alpha;
        point_2i uvB = second_half ? uv[1] + (uv[2] - uv[1]) * betta : uv[0] + (uv[1] - uv[0])*betta;
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
            if (zbuffer_[idx] < P.z)
                set_pixel(P, uvP, idx);

        }
    }
}

void MainWindow::draw_face()
{    
    Matrix matrix_view_port;
    matrix_view_port.view_port(width_/8, height_/8, width_*3/4, height_*3/4);
    Matrix Projection;
    Projection.identity();
    Projection[3][2] = -1.f/(eye_-center_).norm();
    Matrix m  = lookat( eye_, center_, point_3f(0,1,0));
    Matrix multy_matrix = matrix_view_port*Projection*m;
    for (int i = 0; i < faces_.size(); ++i)
    {
        QVector<point_3i> triangle3D = faces_[i];
        point_3i screen_coords[3];
        point_2i tex_coords[3];

        for (int j = 0; j < 3; ++j)
        {
            point_3f verts_triangle = verts_[triangle3D[j].x];
            //std::swap(verts_triangle.x,verts_triangle.z);
            point_2f vt_triangle = vt_[faces_[i][j].y];
            screen_coords[j] = multy_matrix*verts_triangle;
            //screen_coords[j].z = screen_coords[j].z *(-1);
            tex_coords[j] = point_2i(vt_triangle.x * texture_.width(), vt_triangle.y * texture_.height());
        }
        triangle(screen_coords, tex_coords);
    }
    ui->label->setPixmap(QPixmap::fromImage(image_->mirrored(),Qt::AutoColor));
}



