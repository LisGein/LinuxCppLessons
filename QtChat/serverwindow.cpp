#include "serverwindow.h"
#include  <QTextEdit>
#include  <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include  <QPushButton>
#include <QComboBox>
#include <QListWidget>


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
// Third type message - disconnect user
void ServerWindow::connect_signals()
{
  connect(server_network_, SIGNAL(in_message(QString)), this, SLOT(slot_read_in_message(QString)));
  connect(this, SIGNAL(signal_send_server(QByteArray)), server_network_, SLOT(slot_send_to_server(QByteArray)));
  connect(server_network_, SIGNAL(online(QMap<QTcpSocket*, QString>)), this, SLOT(slot_show_online(QMap<QTcpSocket*, QString>)));
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

void ServerWindow::slot_show_online(QMap<QTcpSocket*, QString> connected_users_port)
{
  QWidget* window = new(QWidget);
  QVBoxLayout* window_layout = new QVBoxLayout;

  QMap<QTcpSocket*, QString>::const_iterator it_users_port;
  QListWidget*out_text = new QListWidget;
  int pos = 0;
  for (it_users_port = connected_users_port.begin(); it_users_port != connected_users_port.end(); ++it_users_port)
    {
      QListWidgetItem *qwe = new QListWidgetItem;
      qwe->setText(it_users_port.value());
      out_text->insertItem(pos, qwe);
      pos++;
      //connect(out_texts, SIGNAL(itemClicked(qwe)), window, SLOT(slot_send_to_server())) ;
    }
  window_layout->addWidget(out_text);
  window->setWindowTitle("Online users");
  window->setLayout(window_layout);
  window->show();
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








