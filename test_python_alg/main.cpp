#include <QThread>

class QThread;

class CalcData
        : public QThread
{

};

void main()
{
   AbstractCalcs* c =  new CalcGView;
}
