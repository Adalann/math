#ifndef DEF_POINT
#define DEF_POINT

#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <string>

class Point
{
  public:

    Point();
    Point(double X, double Y);

    Point &operator+=(Point const &p);
    Point &operator*=(double scalaire);

    double getX() const;
    double getY() const;

    void print(std::string comment = "") const;
    void trace(double taille = 0.75, double r = 255, double g = 0, double b = 0) const;

  protected:
  
    double x;
    double y;
};

Point operator+(Point const &p1, Point const &p2);
Point operator*(Point const &p, double scalaire);

#endif