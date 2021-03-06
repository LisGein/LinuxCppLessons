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
#include <QProgressDialog>
#include "confusion_matrix.h"
#include <QThread>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
//    void learn();

private:
  Ui::MainWindow *ui;

  std::string dir_weight_;
  perceptron_t *perceptron_;
  dataset_t *dataset_;
  size_t step_;
  std::atomic<bool> stop_learning_;
  QProgressDialog *progress_;
  QThread* thread_;



signals:
  void ready_result(QString result);
  void finish_learn();

private slots:
  void learning();
  void load_img();
  void open();
  void save();
  void print_result(QString result);
  void learn();
};

