#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stringClient_(new StringClient(3425, this))
{
   ui->setupUi(this);
   login_ = new LogIn();
   login_->show();
   ui->send->setDisabled(true);
   connect(stringClient_, SIGNAL(ready_msg(QString)), this, SLOT(read_message(QString)));
   connect(stringClient_, SIGNAL(ready_online(rapidjson::Document const&)), this, SLOT(show_online(rapidjson::Document const&)));
   connect(ui->send, SIGNAL(clicked()), this, SLOT(send_message()));
   connect(ui->in_text, SIGNAL(returnPressed()), this, SLOT(send_message()));
   connect(login_, SIGNAL(registration(QString)), this, SLOT(entry_chat(QString)));
}

MainWindow::~MainWindow()
{
   delete ui;

}

void MainWindow::entry_chat(QString const &message)
{
    stringClient_->login(message);
    login_->close();
    ui->send->setDisabled(false);
}

void MainWindow::read_message(QString str)
{
    rapidjson::Document d;
    d.Parse(str.toUtf8());
    QByteArray Base64msg = d["msg"].GetString();
    ui->out_text->append(Base64msg);
}

void MainWindow::send_message()
{
    QString message = ui->in_text->text();
    stringClient_->send(message);
    ui->in_text->clear();
}

void MainWindow::show_online(const rapidjson::Document &doc)
{
    ui->list_online->clear();
    for (rapidjson::SizeType i = 0; i < doc["list"].Size(); i++)
      {
        QListWidgetItem *online_user = new QListWidgetItem;
        online_user->setText(doc["list"][i].GetString());
        ui->list_online->insertItem(i, online_user);
      }
}


