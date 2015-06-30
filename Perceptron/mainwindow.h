#pragma once
#include <QMainWindow>
#include "perceptron.h"
#include "dataset_t.h"
#include <memory>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  QString dir_weight_;
  std::unique_ptr<perceptron_t> perceptron_;
  std::unique_ptr<dataset_t> dataset_;
  QImage *image_;

private slots:
  void learning();
  void load_img();
  void open();
  void save();
};

