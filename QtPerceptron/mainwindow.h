#pragma once
#include <QMainWindow>
#include "perceptron.h"
#include "dataset_t.h"
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>
#include "confusion_matrix.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    void learn();

private:
  Ui::MainWindow *ui;

  std::string dir_weight_;
  perceptron_t *perceptron_;
  dataset_t *dataset_;


signals:
  void ready_result(QString result);

private slots:
  void learning();
  void load_img();
  void open();
  void save();
  void print_result(QString result);
};

