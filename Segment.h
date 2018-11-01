#ifndef DEF_SEGMENT
#define DEF_SEGMENT

#include "Point.h"

class Segment
{
    public:

    Segment();
    Segment(Point a, Point B);
    Segment(double x0, double y0, double x1, double y1);

    Point getA() const;
    Point getB() const;
    double getXA() const;
    double getYA() const;
    double getXB() const;
    double getYB() const;

    private:

    Point a;
    Point b;
};

#endif