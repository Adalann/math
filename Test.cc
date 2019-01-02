#include "Point.h"
#include <cmath>
#include <vector>

double carre(double x)
{
    return x * x;
}

Point polynome1(double x)
{
    return Point(x, (2 * pow(x, 2) - 1) / (pow(x, 2) + 2 * x - 3));
}

Point polynome2(double x)
{
    return Point(x, (pow(x, 3) - 4 * pow(x, 2) - 11 * x + 16 ) / (pow(x, 2) + 2 * x - 3));
}

