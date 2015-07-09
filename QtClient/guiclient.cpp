#include "guiclient.h"
#include "ui_guiclient.h"

GuiClient::GuiClient(QByteArray const& nick, int port, QString const& IP_address, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiClient)
{
    ui->setupUi(this);
    stringClient_ = new StringClient(port);
    connect(stringClient_, SIGNAL(ready_msg(QString)), this, SLOT(read_message(QString)));
    connect(ui->send, SIGNAL(clicked()), this, SLOT(send_message()));
    connect(ui->in_text, SIGNAL(returnPressed()), this, SLOT(send_message()));
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

