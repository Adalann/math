#include "Point.h"
#include "Segment.h"

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

Segment::Segment(float x0, float y0, float x1, float y1)
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

float Segment::getXA() const
{
    return a.getX();
}

float Segment::getYA() const
{
    return a.getY();
}

float Segment::getXB() const
{
    return b.getX();
}

float Segment::getYB() const
{
    return b.getY();
}