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

    double getX() const;
    double getY() const;

    void print(std::string comment = "") const;
    void trace(double taille = 0.75, double r = 255, double g = 0, double b = 0) const;

  protected:
  
    double x;
    double y;
};

#endif