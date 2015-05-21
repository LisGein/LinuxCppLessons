#include "serverwindow.h"
#include  <QTextEdit>
#include  <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include  <QPushButton>
#include  <QFont>
#include  <QStyle>


ServerWindow::ServerWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt)
  : QWidget(pwgt)
{
  server_network_ = new ServerNetwork(user_name, str_host, port);
  connect_signals();
  create_main_widget();
  create_menu();
  create_window_chat();
}
// First type message - input message client
// Second type message - show online users
void ServerWindow::connect_signals()
{
  connect(server_network_, SIGNAL(in_message(QString)), this, SLOT(slot_read_in_message(QString)));
  connect(this, SIGNAL(signal_send_server(QByteArray)), server_network_, SLOT(slot_send_to_server(QByteArray)));
  connect(server_network_, SIGNAL(online(QString)), this, SLOT(slot_show_online(QString)));
}

void ServerWindow::create_main_widget()
{
  out_text_ = new QTextEdit;
  out_text_->setReadOnly(true);
  in_text_ = new QLineEdit;
  in_text_->setFixedSize(400, 50);
  connect(in_text_, SIGNAL(returnPressed()), this, SLOT(slot_send_to_server()));

  in_cmd = new QPushButton("&Send");
  connect(in_cmd, SIGNAL(clicked()), SLOT(slot_send_to_server()));
}

void ServerWindow::create_menu()
{
  menu_ = new QMenu("&Menu");
  QAction* show_online = new QAction(tr("&Online users"), this);
  menu_->addAction(show_online);
  menu_->addAction("&Close", this, SLOT(close()));
  menu_bar_.addMenu(menu_);

  connect(show_online, SIGNAL( activated() ), server_network_, SLOT(slot_show_online()) );
}

void ServerWindow::create_window_chat()
{
  QVBoxLayout* window_layout = new QVBoxLayout;
  window_layout->setMenuBar(&menu_bar_);
  window_layout->addWidget(out_text_);
  window_layout->addWidget(in_text_);
  window_layout->addWidget(in_cmd);
  this->setWindowTitle("Chat");
  setLayout(window_layout);
}

void ServerWindow::slot_show_online(QString online_users)
{
  QMessageBox show_online;
  show_online.setText(online_users);
  show_online.show();
  show_online.exec();
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
  out << quint16(0) << FIRST_TYPE << QTime::currentTime() << in_text_->text();

  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  in_text_->setText("");
  emit signal_send_server(arr_block);
}








