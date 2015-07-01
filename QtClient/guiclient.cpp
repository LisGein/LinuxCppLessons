#include "guiclient.h"
#include "ui_guiclient.h"

GuiClient::GuiClient(QString const& nick, int port, QString const& IP_address, QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::GuiClient)
{
   ui->setupUi(this);
   tcp_socket_ = new QTcpSocket;
   tcp_socket_->connectToHost(IP_address, port);
   connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(read_message()));
   connect(ui->send, SIGNAL(clicked()), this, SLOT(send_message()));
   connect(ui->in_text, SIGNAL(returnPressed()), this, SLOT(send_message()));
   QByteArray array_message;
   array_message.append(nick);
   tcp_socket_->write(array_message);
}

GuiClient::~GuiClient()
{
   delete ui;
}

void GuiClient::read_message()
{
   while(tcp_socket_->bytesAvailable()>0)
   {
      QString array_message = tcp_socket_->readAll();
      ui->out_text->append(array_message);
   }
}

void GuiClient::send_message()
{
   QString message = ui->in_text->text();
   QByteArray array_message;
   array_message.append(message);
   tcp_socket_->write(array_message);
   ui->in_text->clear();
}

