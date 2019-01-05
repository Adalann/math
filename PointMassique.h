#ifndef DEF_POINT_MASSIQUE
#define DEF_POINT_MASSIQUE

#include "Point.h"

class PointMassique : public Point
{
  public:

    PointMassique();
    PointMassique(Point p, double W);
    PointMassique(double X, double Y, double W);

    PointMassique &operator+=(PointMassique const &p);
    PointMassique &operator*=(double scalaire);

    double getW() const;

    static Point barycentre(const PointMassique &a, const PointMassique &b);

  private:

    double w;

};

PointMassique operator+(PointMassique const &p1, PointMassique const &p2);
PointMassique operator*(PointMassique const &p, double scalaire);

#endif