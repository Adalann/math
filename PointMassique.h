#ifndef DEF_POINT_MASSIQUE
#define DEF_POINT_MASSIQUE

#include "Point.h"
#include <ostream>

class PointMassique : public Point
{
  public:

    PointMassique();
    PointMassique(const Point &p, float W);
    PointMassique(float X, float Y, float W);

    PointMassique &operator+=(PointMassique const &p);
    PointMassique &operator*=(float scalaire);

    float getW() const;

    void display() const;

    static Point barycentre(const PointMassique &a, const PointMassique &b);
    friend std::ostream &operator<<(std::ostream &stream, PointMassique &p);

  private:

    float w;

};

PointMassique operator+(PointMassique const &p1, PointMassique const &p2);
PointMassique operator*(PointMassique const &p, float scalaire);

#endif