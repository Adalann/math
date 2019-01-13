#ifndef DEF_SEGMENT
#define DEF_SEGMENT

#include "Point.h"

class Segment
{
    public:

    Segment();
    Segment(Point a, Point B);
    Segment(float x0, float y0, float x1, float y1);

    Point getA() const;
    Point getB() const;
    float getXA() const;
    float getYA() const;
    float getXB() const;
    float getYB() const;

    private:

    Point a;
    Point b;
};

#endif