#ifndef DEF_POINT_MASSIQUE
#define DEF_POINT_MASSIQUE

#include "Point.h"
#include <ostream>

class PointMassique : public Point
{
  public:

    PointMassique();
    PointMassique(const Point &p, double W);
    PointMassique(double X, double Y, double W);

    PointMassique &operator+=(PointMassique const &p);
    PointMassique &operator*=(double scalaire);

    double getW() const;

    void display() const;

    static Point barycentre(const PointMassique &a, const PointMassique &b);
    friend std::ostream &operator<<(std::ostream &stream, PointMassique &p);

  private:

    double w;

};

PointMassique operator+(PointMassique const &p1, PointMassique const &p2);
PointMassique operator*(PointMassique const &p, double scalaire);

#endif