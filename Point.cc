#include "Point.h"

Point::Point()
{
    x = 0.;
    y = 0.;
}

Point::Point(double X, double Y)
{
    x = X;
    y = Y; 
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}