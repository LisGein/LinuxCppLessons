#pragma once
#include <QMainWindow>
#include "perceptron.h"
#include "dataset_t.h"
#include <vector>

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

  std::string dir_weight_;
  perceptron_t *perceptron_;
  dataset_t *dataset_;

private slots:
  void learning();
  void load_img();
  void open();
  void save();
};

