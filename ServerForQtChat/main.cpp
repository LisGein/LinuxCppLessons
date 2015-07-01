#include <stdlib.h>
#include "network.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ServerNetwork serverNetwork("localhost", 3425);
  return a.exec();
}

