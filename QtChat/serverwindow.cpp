#include "serverwindow.h"
#include  <QTextEdit>
#include  <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include  <QPushButton>

ServerWindow::ServerWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt)
  : QWidget(pwgt)
{
  ServerNetwork *server_network = new ServerNetwork(user_name, str_host, port);
  connect(server_network, SIGNAL(in_message(QString)), this, SLOT(slot_read_in_message(QString)));
  connect(this, SIGNAL(signal_send_server(QByteArray)), server_network, SLOT(slot_send_to_server(QByteArray)));

  out_text_ = new QTextEdit;
  out_text_->setReadOnly(true);
  in_text_ = new QLineEdit;
  in_text_->setFixedSize(400, 50);
  connect(in_text_, SIGNAL(returnPressed()), this, SLOT(slot_send_to_server()));

  QPushButton* in_cmd = new QPushButton("&Send");
  connect(in_cmd, SIGNAL(clicked()), SLOT(slot_send_to_server()));

  QVBoxLayout* window_layout = new QVBoxLayout;
  window_layout->addWidget(new QLabel("<H1>Server</H1>"));
  window_layout->addWidget(out_text_);
  window_layout->addWidget(in_text_);
  window_layout->addWidget(in_cmd);
  setLayout(window_layout);
}

void ServerWindow::slot_read_in_message(QString str)
{
  out_text_->append(str);
}

void ServerWindow::slot_send_to_server()
{
  QByteArray arr_block;
  QDataStream out(&arr_block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << QTime::currentTime() << in_text_->text();

  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  in_text_->setText("");
  emit signal_send_server(arr_block);
}

void ServerWindow::slot_show_menu(){}
