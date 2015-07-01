#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   Server w(3425, "127.0.0.1");//"109.234.35.126");

   return a.exec();
}
