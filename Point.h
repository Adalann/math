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
    Point(float X, float Y);

    Point &operator+=(Point const &p);
    Point &operator*=(float scalaire);

    float getX() const;
    float getY() const;

    void print(std::string comment = "") const;
    void trace(float taille = 0.75, float r = 255, float g = 0, float b = 0) const;

  protected:
  
    float x;
    float y;
};

Point operator+(Point const &p1, Point const &p2);
Point operator*(Point const &p, float scalaire);

#endif