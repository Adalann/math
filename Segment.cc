#include "Point.h"
#include "Segment.h"

using namespace std;

Segment::Segment()
{
    a = Point(0., 0.);
    b = Point(1., 1.);
}

Segment::Segment(Point A, Point B)
{
    a = A;
    b = B;
}

Segment::Segment(double x0, double y0, double x1, double y1)
{
    a = Point(x0, y0);
    b = Point(x1, y1);
}

Point Segment::getA() const
{
    return a;
}

Point Segment::getB() const
{
    return b;
}

double Segment::getXA() const
{
    return a.getX();
}

double Segment::getYA() const
{
    return a.getY();
}

double Segment::getXB() const
{
    return b.getX();
}

double Segment::getYB() const
{
    return b.getY();
}