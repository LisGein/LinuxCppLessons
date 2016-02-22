#include <QCoreApplication>


struct ConstPoint
{
   ConstPoint()
      : x_(0)
      , y_(0)
   {}
   ConstPoint(int x, int y)
      : x_(x)
      , y_(y)
   {}
   ~ConstPoint();
   int getX() const { return x_;}
   int getY() const { return y_;}
   const ConstPoint  operator +(const ConstPoint& point)
   {
      return ConstPoint(point.getX() + x_, point.getY()+y_);
   }
   const ConstPoint  operator -(const ConstPoint& point)
   {
      return ConstPoint(point.getX() - x_, point.getY()-y_);
   }
   const ConstPoint operator =(const ConstPoint& point)
   {
      return ConstPoint(point.getX(), point.getY());
   }
   bool operator !=(const ConstPoint& point)
   {
      return (x_ == point.getX() && y_ == point.getY());
   }
   bool	isNull() const
   {
      return (x_ == 0 && y_ == 0);
   }
   const ConstPoint setX(int x)
   {
      return ConstPoint(x, y_);
   }
   const ConstPoint setY(int y)
   {
      return ConstPoint(x_, y);
   }
   const ConstPoint operator*=(double factor)
   {
      return ConstPoint(x_ * factor, y_ * factor);
   }
   const ConstPoint  operator +=(const ConstPoint& point)
   {
      return ConstPoint(x_ + point.getX(), y_ + point.getY());
   }
   const ConstPoint  operator -=(const ConstPoint& point)
   {
      return ConstPoint(x_ - point.getX(), y_ - point.getY());
   }
private:
   int x_;
   int y_;
};
/*
QPoint &	operator+=(const QPoint & point)
QPoint &	operator-=(const QPoint & point)
QPoint &	operator/=(qreal divisor)
*/

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   return a.exec();
}
