#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


const size_t X_SIZE = 256;
const size_t Y_SIZE = 10;
const size_t EPOCH_COUNT = 100;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dir_weight_("0")
    , step_(0)
    , stop_learning_(false)
{
    ui->setupUi(this);
    connect(ui->learn, SIGNAL(clicked()),SLOT(learning()));
    connect(ui->load,  SIGNAL(clicked()),SLOT(load_img()));
    connect(ui->open,  SIGNAL(clicked()),SLOT(open()));
    connect(ui->close,  SIGNAL(clicked()),SLOT(close()));
    ui->textEdit->setReadOnly(true);
    ui->load->setDisabled(true);
    connect(ui->save,  SIGNAL(clicked()),SLOT(save()));
    connect(this,  SIGNAL(ready_result(QString)),SLOT(print_result(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print_result(QString result)
{
    ui->textEdit->append(result);
}

void MainWindow::learn()
{
    ConfusionMatrix confusion_matrix(Y_SIZE);
    if (dir_weight_ == "0")
        perceptron_->create_weight();

    size_t i = 0;
    for (; i <  EPOCH_COUNT; ++i)
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
        emit ready_result(valueAsString);
        confusion_matrix.clear_confusion_matrix();
        if (stop_learning_ == true)
        {
            stop_learning_ = false;
            break;
        }
        emit incremtent_progress();
    }
    if (i == EPOCH_COUNT)
    {
        emit incremtent_progress();
        emit ready_result("end learning");
    }
}

void MainWindow::run_progress()
{
    progress_->setValue(step_);
    step_++;
    if (progress_->wasCanceled())
    {
        stop_learning_ = true;
        step_ = 0;
        delete progress_;
    }
}

void MainWindow::learning()
{
    QString dir_weight = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text (*.txt)"));
    dataset_ = new dataset_t(dir_weight.toStdString(), X_SIZE, Y_SIZE);
    dataset_->split_train_test(0.7);
    perceptron_ = new perceptron_t(dataset_->dim());
    std::thread learning_thread(&MainWindow::learn, this);
    learning_thread.detach();

    progress_ = new QProgressDialog("Learning...", "Cancel", 0, EPOCH_COUNT - 1, this);
    connect(progress_, SIGNAL(canceled()), progress_, SLOT(cancel()));
    progress_->setWindowModality(Qt::WindowModal);
    connect(this, SIGNAL(incremtent_progress()),SLOT(run_progress()));

    ui->load->setDisabled(false);

}

void MainWindow::load_img()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.xpm *.jpg)"));
    QImage img(16, 16, QImage::Format_RGB32);
    img.load(fileName);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->show();
    std::vector<double> data;
    for ( int row = 0; row < img.height(); ++row )
        for ( int col = 0; col < img.width(); ++col )
        {
            QColor clrCurrent( img.pixel( row, col ) );
            if ((clrCurrent.red()==255)&&(clrCurrent.green()==255)&&(clrCurrent.blue()==255))
                data.push_back(1);
            else
                data.push_back(0);
        }
    std::vector<char> return_classify = perceptron_->classify(data);
    int result;
    for (int i = 0; i < return_classify.size();++i)
        if (return_classify[i] == 1)
            result = i;
    QString valueAsString = QString::number(result);
    ui->textEdit->append(valueAsString);
}

void MainWindow::open()
{
    QString dir_weight = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text (*.txt)"));
    dir_weight_=dir_weight.toUtf8().constData();

    perceptron_->load(dir_weight_);
    ui->load->setDisabled(false);
    ui->textEdit->append("Uploaded");
}

void MainWindow::save()
{
    perceptron_->save();
    ui->textEdit->append("Saved");
}
