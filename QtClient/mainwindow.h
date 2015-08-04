#pragma once
#include "stringclient.h"
#include <QMainWindow>
#include <QAudioInput>
#include <QAudioOutput>
#include "registration.h"
#include <QListWidgetItem>
#include "insetdialog.h"

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT


public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:
   Ui::MainWindow *ui;
   StringClient *stringClient_;
   Registration *registration_;
   QMap < QString, InsetDialog*> opened_tabs_;
   QUdpSocket* udpSocket_;
   QUdpSocket* udpRecv_;
   QAudioInput* qAudioInput_;
   QAudioOutput* qAudioOutput_;
   QIODevice *device_;

private slots:
   void show_online(rapidjson::Document const & doc);
   void create_private(QListWidgetItem* select_user);
   void read_private_message(QString str);
   void send(QString message);
   void start_broadcast_audio();
   void stop_broadcast_audio();
   void create_udp(QString const& name, const QString &IP);
   void play_audio();

signals:
   void ready();
};

