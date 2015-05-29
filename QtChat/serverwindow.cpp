#include "serverwindow.h"
#include  <QTextEdit>
#include  <QLineEdit>
#include <QLabel>
#include  <QPushButton>
#include <QComboBox>
#include <QCloseEvent>


ServerWindow::ServerWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt)
  : QWidget(pwgt)
{
  server_network_ = new ServerNetwork(user_name, str_host, port);
  server_online_window_ = new ListOnline();
  connect_signals();
  create_main_widget();
  create_menu();
  create_window_chat();
}
// First type message - input message client
// Second type message - show online users

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

  connect(show_online, SIGNAL( activated() ), this, SLOT(slot_open_online()) );
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

void ServerWindow::connect_signals()
{
  connect(server_network_, SIGNAL(in_message(QString)), this, SLOT(slot_read_in_message(QString)));
  connect(this, SIGNAL(signal_send_server(QByteArray)), server_network_, SLOT(slot_send_to_server(QByteArray)));
  connect(server_online_window_, SIGNAL(signal_del_user(QTcpSocket*)), server_network_, SLOT(slot_delete_user(QTcpSocket*)));
  connect(server_network_, SIGNAL(refresh(QMap<QString, QTcpSocket*>)), server_online_window_, SLOT(slot_refresh(QMap<QString, QTcpSocket*>)));
//  //connect(server_network_, SIGNAL(online(QMap<QString, QTcpSocket*>)), server_online_window_, SLOT(slot_refresh(QMap<QString, QTcpSocket*>)));
//  connect(server_online_window_, SIGNAL(signal_refresh_online()), server_network_, SLOT(slot_refresh()));
  connect(this, SIGNAL(signal_close_online()), server_network_, SLOT(slot_close_online()));
  connect(this, SIGNAL(signal_open_online() ), server_network_, SLOT(slot_refresh()) );
}

void ServerWindow::slot_open_online()
{
  server_online_window_->show();
  emit signal_open_online();
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
  out << quint16(0) << FIRST_TYPE << in_text_->text();

  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  in_text_->setText("");
  emit signal_send_server(arr_block);
}
