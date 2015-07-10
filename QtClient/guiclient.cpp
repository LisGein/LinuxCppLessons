#include "guiclient.h"
#include "ui_guiclient.h"

GuiClient::GuiClient(QByteArray const& nick, int port, QString const& IP_address, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GuiClient)
    , stringClient_(new StringClient(port, this))

{
    ui->setupUi(this);
    connect(stringClient_, SIGNAL(ready_msg(QString)), this, SLOT(read_message(QString)));
    connect(stringClient_, SIGNAL(ready_online(rapidjson::Document const&)), this, SLOT(show_online(rapidjson::Document const&)));
    connect(ui->send, SIGNAL(clicked()), this, SLOT(send_message()));
    connect(ui->in_text, SIGNAL(returnPressed()), this, SLOT(send_message()));
    connect (ui->actionOnline_users, SIGNAL(triggered(bool)), stringClient_, SLOT(request_list_online()));
    stringClient_->login(nick);
}

GuiClient::~GuiClient()
{
    delete ui;
}

void GuiClient::read_message(QString str)
{
    rapidjson::Document d;
    d.Parse(str.toUtf8());
    QByteArray Base64msg = d["msg"].GetString();
    ui->out_text->append(Base64msg);
}

void GuiClient::send_message()
{
    QString message = ui->in_text->text();
    stringClient_->send(message);
    ui->in_text->clear();
}

void GuiClient::show_online(const rapidjson::Document &doc)
{
    ui->list_online->clear();
    for (rapidjson::SizeType i = 0; i < doc["list"].Size(); i++)
      {
        QListWidgetItem *online_user = new QListWidgetItem;
        online_user->setText(doc["list"][i].GetString());
        ui->list_online->insertItem(i, online_user);
      }
}
