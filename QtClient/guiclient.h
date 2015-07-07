#pragma once
#include <QMainWindow>
#include "stringclient.h"

namespace Ui {
   class GuiClient;
}

class GuiClient : public QMainWindow
{
   Q_OBJECT

public:
   explicit GuiClient(const QByteArray &nick, int port, QString const& IP_address, QWidget *parent = 0);
   ~GuiClient();
private slots:
   void read_message(QString str);
   void send_message();

signals:
   void send(QString);

private:
   Ui::GuiClient *ui;

   StringClient *stringClient_;
};

