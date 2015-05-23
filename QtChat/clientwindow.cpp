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
  connect(client_network_, SIGNAL(online(QString)), this, SLOT(slot_show_online(QString)));
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
  connect(show_online, SIGNAL( activated() ), client_network_, SLOT(slot_show_online_cl()) );
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

void ClientWindow::slot_show_online(QString online_users)
{
  QMessageBox show_online;
  show_online.setText(online_users);
  show_online.show();
  show_online.exec();
}
