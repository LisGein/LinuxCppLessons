#include "clientwindow.h"
#include  <QTextEdit>
#include  <QLineEdit>
#include  <QVBoxLayout>
#include  <QPushButton>
#include  <QLabel>
#include <QMenuBar>

ClientWindow::ClientWindow(const QByteArray &user_name, const QString& str_host, int port, QWidget* pwgt)
  : QWidget(pwgt)
{
  client_network_ = new ClientNetwork(user_name, str_host, port);
  online_clients_ = new ListOnlineClient();
  connect_signals();
  create_main_widget();
  create_menu();
  create_window_chat();
}
// First type message - input message client
// Second type message - show online users
void ClientWindow::connect_signals()
{
  connect(client_network_, SIGNAL(in_message(QString)), this, SLOT(slot_ready_read(QString)));
  connect(this, SIGNAL(signal_send_server(QByteArray)), client_network_, SLOT(slot_send_message(QByteArray)));
  connect(client_network_, SIGNAL(online(QString)), online_clients_, SLOT(slot_refresh(QString)));
  //connect(this, SIGNAL(signal_close_online()), client_network_, SLOT(slot_close_online()));
  connect(this, SIGNAL(signal_open_online() ), client_network_, SLOT(slot_show_online_cl()) );
}

void ClientWindow::slot_open_online()
{
  online_clients_->show();
  emit signal_open_online();
}

void ClientWindow::create_main_widget()
{
  out_text_  = new QTextEdit;
  out_text_->setReadOnly(true);
  in_text_ = new QLineEdit;
  connect(in_text_, SIGNAL(returnPressed()), this, SLOT(slot_send_to_server()));
  in_cmd = new QPushButton("&Send");
  connect(in_cmd, SIGNAL(clicked()), SLOT(slot_send_to_server()));
}

void ClientWindow::create_menu()
{
  menu_ = new QMenu("&Menu");
  QAction* show_online = new QAction(tr("&Online users"), this);
  menu_->addAction(show_online);
  menu_->addAction("&Close", this, SLOT(close()));
  menu_bar_.addMenu(menu_);
  connect(show_online, SIGNAL( activated() ), this, SLOT(slot_open_online()) );
}

void ClientWindow::create_window_chat()
{
  QVBoxLayout* window_layout = new QVBoxLayout;
  window_layout->setMenuBar(&menu_bar_);
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
  out << quint16(0) << FIRST_TYPE_MSG << in_text_->text();

  out.device()->seek(0);
  out << quint16(arr_block.size() - sizeof(quint16));
  in_text_->setText("");
  emit signal_send_server(arr_block);
}

void ClientWindow::slot_ready_read(QString str)
{
  out_text_->append(str);
}

