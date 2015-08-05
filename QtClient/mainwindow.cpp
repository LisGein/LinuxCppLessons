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
    connect(registration_, SIGNAL(login(QString, QString)), this, SLOT(create_udp(QString, QString)));
    registration_->exec();
    connect(stringClient_, SIGNAL(ready_private_msg(QString)), this, SLOT(read_private_message(QString)));
    connect(stringClient_, SIGNAL(ready_online(rapidjson::Document const&)), this, SLOT(show_online(rapidjson::Document const&)));
    InsetDialog *inset = new InsetDialog("Global");
    inset->show();
    ui->tabWidget->insertTab(opened_tabs_.size(), inset, "Global");
    connect(inset, SIGNAL(send(QString)), SLOT(send(QString)));
    opened_tabs_.insert("Global", inset);

    QAudioFormat format;
    format.setSampleSize(8);
    format.setSampleRate(8000);
    format.setCodec("audio/pcm");
    format.setChannelCount(1);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    qAudioInput_ = new QAudioInput(format, this);
    qAudioOutput_ = new QAudioOutput(format, this);
    connect(ui->record, SIGNAL(pressed()), this, SLOT(start_broadcast_audio()));
    connect(ui->record, SIGNAL(released()), this, SLOT(stop_broadcast_audio()));
    device_ = qAudioOutput_->start();
    device_->open(QIODevice::ReadWrite);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::play_audio()
{
    qDebug() << "sefwf";

    //qAudioOutput_->start();
    while (udpRecv_->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(udpRecv_->pendingDatagramSize());
        udpRecv_->readDatagram(data.data(), data.size());
        device_->write(data, data.size());
    }
    //qAudioOutput_->stop();
}

void MainWindow::create_udp(QString const& name, const QString &IP)
{
    udpSocket_ = new QUdpSocket;
    udpRecv_  = new QUdpSocket;
    QHostAddress address;
    address.setAddress(IP);
    udpSocket_->connectToHost(QHostAddress::Any, 3425);
    udpRecv_->bind(3325);
    connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(play_audio()));
    connect(udpRecv_, SIGNAL(readyRead()), this, SLOT(play_audio()));
}

void MainWindow::start_broadcast_audio()
{
    qAudioInput_->start(udpSocket_);
}

void MainWindow::stop_broadcast_audio()
{
    qAudioInput_->stop();
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
