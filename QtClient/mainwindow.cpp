#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stringClient_(new StringClient(3425, this))
{
    auto dialog = new QDialog(this);
    ui->setupUi(this);
    registration_ = new Registration(dialog);
    connect(registration_, SIGNAL(login(QString)), stringClient_, SLOT(login(QString)));
    registration_->exec();
    connect(stringClient_, SIGNAL(ready_private_msg(QString)), this, SLOT(read_private_message(QString)));
    connect(stringClient_, SIGNAL(ready_online(rapidjson::Document const&)), this, SLOT(show_online(rapidjson::Document const&)));
    InsetDialog *inset = new InsetDialog("Global");
    inset->show();
    ui->tabWidget->insertTab(opened_tabs_.size(), inset, "Global");
    connect(inset, SIGNAL(send(QString)), SLOT(send(QString)));
    opened_tabs_.insert("Global", inset);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::send(QString message)
{
    stringClient_->send(message);
}

void MainWindow::show_online(const rapidjson::Document &doc)
{
    ui->list_online->clear();
    for (rapidjson::SizeType i = 0; i < doc["list"].Size(); i++)
    {
        QListWidgetItem *online_user = new QListWidgetItem;
        online_user->setText(doc["list"][i].GetString());
        ui->list_online->insertItem(i, online_user);
        connect(ui->list_online, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(create_private(QListWidgetItem*)));
    }
}

void MainWindow::create_private(QListWidgetItem* select_user)
{
    auto it_1 = opened_tabs_.find(select_user->text());
    if (it_1 == opened_tabs_.end())
    {
        InsetDialog *inset = new InsetDialog(select_user->text());
        inset->show();
        ui->tabWidget->insertTab(opened_tabs_.size(), inset, select_user->text());
        connect(inset, SIGNAL(send(QString)), SLOT(send(QString)));
        opened_tabs_.insert(select_user->text(), inset);
    }
}

void MainWindow::read_private_message(QString str)
{
    rapidjson::Document d;
    d.Parse(str.toUtf8());
    QString name = d["name"].GetString();

    QByteArray Base64msg;
    Base64msg.append(name + ": ");
    Base64msg.append(d["msg"].GetString());
    QString type = d["type"].GetString();
    qDebug() << Base64msg;
    QString addressee = d["addressee"].GetString();
        auto it_1 = opened_tabs_.find(name);
        auto it_2 = opened_tabs_.find(addressee);
        if (name == stringClient_->nick_name())
            name = addressee;
        else if (type != "private")
            name = "Global";
        if ((it_1 == opened_tabs_.end())&&(it_2 == opened_tabs_.end()))
        {
            InsetDialog *inset = new InsetDialog(name);
            inset->show();
            ui->tabWidget->insertTab(opened_tabs_.size(), inset, name);
            inset->read_message(Base64msg);
            connect(inset, SIGNAL(send(QString)), SLOT(send(QString)));
            opened_tabs_.insert(name, inset);
        }
        else
        {
            auto it =opened_tabs_.find(name);
            it.value()->read_message(Base64msg);
        }


}
