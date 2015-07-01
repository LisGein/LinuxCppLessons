#pragma once
#include <QTcpSocket>
#include <QMainWindow>

namespace Ui {
   class GuiClient;
}

class GuiClient : public QMainWindow
{
   Q_OBJECT

public:
   explicit GuiClient(QString const& nick, int port, QString const& IP_address, QWidget *parent = 0);
   ~GuiClient();
private slots:
   void read_message();
   void send_message();

private:
   Ui::GuiClient *ui;
   QTcpSocket* tcp_socket_;
};

