#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "confusion_matrix.h"
#include <QDialogButtonBox>

const size_t X_SIZE = 256;
const size_t Y_SIZE = 10;
const size_t EPOCH_COUNT = 100;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->learn, SIGNAL(clicked()),SLOT(learning()));
  connect(ui->load,  SIGNAL(clicked()),SLOT(load_img()));
  connect(ui->actionOpen,  SIGNAL(triggered()),SLOT(open()));
  connect(ui->actionClose,  SIGNAL(triggered()),SLOT(close()));
  ui->textEdit->setReadOnly(true);
  ui->load->setDisabled(true);
  connect(ui->actionSave,  SIGNAL(triggered()),SLOT(save()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::learning()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.txt"));
  if (fileName!="")
    {
      dataset_.reset(new dataset_t(fileName.toStdString(), X_SIZE, Y_SIZE));
      dataset_->split_train_test(0.7);
      ConfusionMatrix confusion_matrix(Y_SIZE);
      if (dir_weight_ == "")
        perceptron_.reset(new perceptron_t(dataset_->dim()));

      for (size_t i = 0; i <  EPOCH_COUNT; ++i)
        {
          size_t correct_train = 0;
          for(auto const &sample: dataset_->train_dataset())
            {
              bool correct = perceptron_->learn(sample);
              if (correct)
                correct_train += 1;
            }

          size_t correct_test = 0;
          for(auto const &sample: dataset_->test_dataset())
            {
              std::vector<char> return_classify = perceptron_->classify(sample.first);
              bool correct = return_classify == sample.second;
              if (correct)
                correct_test += 1;
              confusion_matrix.increment(return_classify, sample.second);
            }

          double F = confusion_matrix.f_1();
          QString valueAsString = "test train precision: " + QString::number(F);
          ui->textEdit->append(valueAsString);
          confusion_matrix.clear_confusion_matrix();
        }
      ui->load->setDisabled(false);
    }
}

void MainWindow::load_img()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.xpm *.jpg)"));
  if (fileName!="")
    {
      image_ = new QImage(16, 16, QImage::Format_RGB32);
      image_->load(fileName);
      ui->label->setPixmap(QPixmap::fromImage(*image_));
      ui->label->show();
      std::vector<double> data;
      for ( int row = 0; row < image_->height(); ++row )
        for ( int col = 0; col < image_->width(); ++col )
          {
            QColor clrCurrent( image_->pixel( col, row ) );
            if ((clrCurrent.red()==255)&&(clrCurrent.green()==255)&&(clrCurrent.blue()==255))
              data.push_back(1);
            else
              data.push_back(0);
          }
      std::vector<char> return_classify = perceptron_->classify(data);
      int result;
      for (size_t i = 0; i < return_classify.size();++i)
        if (return_classify[i] == 1)
          result = i;
      QString valueAsString = QString::number(result);
      ui->textEdit->setText(valueAsString);
    }
}

void MainWindow::open()
{

  QString dir_weight = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text (*.txt)"));
  dir_weight_=dir_weight.toUtf8().constData();

  perceptron_.reset(new perceptron_t(dataset_->dim(), dir_weight_.toStdString()));
  ui->load->setDisabled(false);
  ui->textEdit->setText("Uploaded");
}

void MainWindow::save()
{
  perceptron_->save();
  ui->textEdit->setText("Saved");
}
