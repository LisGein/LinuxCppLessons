#include "clientwindow.h"
#include  <QTextEdit>
#include  <QLineEdit>
#include  <QVBoxLayout>
#include  <QTime>
#include  <QPushButton>
#include  <QLabel>
#include <QMenuBar>

ClientWindow::ClientWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt)
  : QWidget(pwgt)
{

  ClientNetwork *client = new ClientNetwork(user_name, str_host, port);
  connect(client, SIGNAL(in_message(QString)), this, SLOT(slot_ready_read(QString)));
  connect(this, SIGNAL(signal_send_server(QByteArray)), client, SLOT(slot_send_message(QByteArray)));

  out_text_  = new QTextEdit;
  out_text_->setReadOnly(true);
  in_text_ = new QLineEdit;
  connect(in_text_, SIGNAL(returnPressed()), this, SLOT(slot_send_to_server()));

  QPushButton* in_cmd = new QPushButton("&Send");
  connect(in_cmd, SIGNAL(clicked()), SLOT(slot_send_to_server()));

  menu_action_ = new QAction(tr("&Show online users"), this);
  connect(menu_action_, SIGNAL( activated() ), this, SLOT( slot_show_menu() ) );
  menu_bar_ = new QMenuBar(this);
  menu_bar_->addAction(menu_action_);

  QVBoxLayout* window_layout = new QVBoxLayout;
  window_layout->addWidget(menu_bar_);
  window_layout->addWidget(out_text_);
  window_layout->addWidget(in_text_);
  window_layout->addWidget(in_cmd);
  this->setWindowTitle("Chat");
  setLayout(window_layout);

}

void ClientWindow::slot_send_to_server()
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

void ClientWindow::slot_ready_read(QString str)
{
  out_text_->append(str);
}

void ClientWindow::slot_show_menu(){}
