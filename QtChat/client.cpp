#include "client.h"

#include  <QTextEdit>
#include  <QLineEdit>
#include  <QVBoxLayout>
#include  <QTime>
#include  <QPushButton>
#include  <QLabel>

Client::Client(const QString& user_name, const QString& strHost, int nPort, QWidget* pwgt)
  : QWidget(pwgt)
  , next_block_size_(0)
  , user_name_(user_name)
{
  tcp_socket_ = new QTcpSocket(this);

  tcp_socket_->connectToHost(strHost, nPort);
  connect(tcp_socket_, SIGNAL(connected()), SLOT(slot_connected()));
  connect(tcp_socket_, SIGNAL(readyRead()), SLOT(slot_ready_read()));
  connect(tcp_socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_error(QAbstractSocket::SocketError)));

  out_text_  = new QTextEdit;
  out_text_->setReadOnly(true);
  in_text_ = new QLineEdit;

  connect(in_text_, SIGNAL(returnPressed()), this, SLOT(slot_send_to_server()));

  QPushButton* in_cmd = new QPushButton("&Send");
  connect(in_cmd, SIGNAL(clicked()), SLOT(slot_send_to_server()));

  //Layout setup
  QVBoxLayout* window_layout = new QVBoxLayout;
  window_layout->addWidget(new QLabel("<H1>Client</H1>"));
  window_layout->addWidget(out_text_);
  window_layout->addWidget(in_text_);
  window_layout->addWidget(in_cmd);
  setLayout(window_layout);
}

void Client::slot_ready_read()
{
  QDataStream in(tcp_socket_);
  in.setVersion(QDataStream::Qt_4_2);
  for (;;)
    {
      if (!next_block_size_)
        {
          if (tcp_socket_->bytesAvailable() < sizeof(quint16))
            break;
          in >> next_block_size_;
        }

      if (tcp_socket_->bytesAvailable() < next_block_size_)
        break;
      QTime   time;
      QString str;
      in >> time >> str;

      out_text_->append(str);
      next_block_size_ = 0;
    }
}
void Client::slot_error(QAbstractSocket::SocketError err)
{
  QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                    "The host was not found." :
                                    err == QAbstractSocket::RemoteHostClosedError ?
                                      "The remote host is closed." :
                                      err == QAbstractSocket::ConnectionRefusedError ?
                                        "The connection was refused." :
                                        QString(tcp_socket_->errorString())
                                        );
  out_text_->append(strError);
}
void Client::slot_send_to_server()
{
  QByteArray  arrBlock;
  QDataStream out(&arrBlock, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_2);
  out << quint16(0) << QTime::currentTime() << in_text_->text();

  out.device()->seek(0);
  out << quint16(arrBlock.size() - sizeof(quint16));

  tcp_socket_->write(arrBlock);
  in_text_->setText("");
}
void Client::slot_connected()
{
  out_text_->append("Received the connected() signal");
}
