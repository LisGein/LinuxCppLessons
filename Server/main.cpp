#include "server.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
   Server server(3425);

   return a.exec();
}
