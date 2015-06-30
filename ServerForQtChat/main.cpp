#include <stdlib.h>
#include <iostream>
#include "network.h"
#include <memory>

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ServerNetwork serverNetwork("localhost", 3425);
  return a.exec();
}

