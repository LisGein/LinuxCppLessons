#include <QCoreApplication>
#include <QDebug>


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
	~ConstPoint() {}
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
	const bool operator !=(const ConstPoint& point)
	{
		return x_ != point.getX() && y_ != point.getY();
	}
	const ConstPoint setX(int x) const
	{
		return ConstPoint(x, y_);
	}
	const ConstPoint setY(int y) const
	{
		return ConstPoint(x_, y);
	}
	const ConstPoint operator*(double factor)
	{
		return ConstPoint(x_ * factor, y_ * factor);
	}

private:
	const int x_;
	const int y_;

	const ConstPoint& operator =(const ConstPoint& point);
	ConstPoint(const ConstPoint& point);
};

QDebug operator<<(QDebug dbg, const ConstPoint& point)
{
	dbg.nospace() << "( " << point.getX() << ", " << point.getY() << " )";
	return dbg.space();
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ConstPoint point(1, 2);
	qDebug() << point;

	return a.exec();
}
