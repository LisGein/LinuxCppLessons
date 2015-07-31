#pragma once
#include <QMainWindow>
#include <QPair>
#include "dataalternativereality.h"
#include "labyrinth.h"

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
    void start_sleep(int width, int height,int R, int G, int B, int Y, QString description);
    void message_error(QString error_var);
    void restart_input();

private:
    Ui::MainWindow *ui;
    DataAlternativeReality *alt_reality_;
    QImage *labyrinth_img_;
    int pos_;
    int width_;
    int height_;
    Labyrinth *labyrinth_;

    void draw_color(QRgb color, QPair<int, int> current_coor);
    int calc_free_road(int R, int G, int B, int Y);
    QPair<int, int> calc_coor();
};

