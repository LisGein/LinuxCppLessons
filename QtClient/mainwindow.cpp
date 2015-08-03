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
    connect(registration_, SIGNAL(login(QString, QString)), stringClient_, SLOT(login(QString, QString)));
    registration_->exec();
    connect(stringClient_, SIGNAL(ready_private_msg(QString)), this, SLOT(read_private_message(QString)));
    connect(stringClient_, SIGNAL(ready_online(rapidjson::Document const&)), this, SLOT(show_online(rapidjson::Document const&)));
    InsetDialog *inset = new InsetDialog("Global");
    inset->show();
    ui->tabWidget->insertTab(opened_tabs_.size(), inset, "Global");
    connect(inset, SIGNAL(send(QString)), SLOT(send(QString)));
    opened_tabs_.insert("Global", inset);
    audioRecorder_ = new QAudioRecorder;
    connect(ui->record, SIGNAL(pressed()), audioRecorder_, SLOT(record()));
    connect(ui->record, SIGNAL(released()), audioRecorder_, SLOT(stop()));

    audioRecorder_->setAudioInput(audioRecorder_->defaultAudioInput());
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/PCM");

    audioRecorder_->setContainerFormat("wav");
    audioSettings.setSampleRate(16000);
    audioSettings.setBitRate(32);
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
    audioRecorder_->setEncodingSettings(audioSettings);
    audioRecorder_->setOutputLocation(QUrl::fromLocalFile("Test.wav"));

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

    QString addressee = d["addressee"].GetString();
    QString type = d["type"].GetString();
    if (name == stringClient_->nick_name())
        name = addressee;
    else if (type != "private")
        name = "Global";
    auto it_1 = opened_tabs_.find(name);

    if (it_1 == opened_tabs_.end())
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
        auto it = opened_tabs_.find(name);
        it.value()->read_message(Base64msg);
    }


}
