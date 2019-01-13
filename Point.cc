#include "Point.h"
#include <iostream>

using namespace std;

Point::Point()
{
    x = 0.;
    y = 0.;
}

Point::Point(float X, float Y)
{
    x = X;
    y = Y; 
}

Point &Point::operator+=(Point const &p)
{
    x += p.x;
    y += p.y;

    return *this;
}

Point &Point::operator*=(float scalaire)
{
    x *= scalaire;
    y *= scalaire;

    return *this;
}

float Point::getX() const
{
    return x;
}

float Point::getY() const
{
    return y;
}

void Point::print(string comment) const
{
    cout << comment << " x = " << x << ", y = " << y << endl;
}

void Point::trace(float taille, float r, float g, float b) const
{
    glColor3f(r, g, b);   // initialisation de la couleur
    glPointSize(taille);  // initialisation de la taille
    glBegin(GL_POINTS);   // on trace un point
    glVertex2f(x, y);     // coordonnees du point
    glEnd();

}

Point operator+(Point const &p1, Point const &p2)
{
    Point copie(p1);
    copie += p2;

    return copie;
}

Point operator*(Point const &p, float scalaire)
{
    Point copie(p);
    copie *= scalaire;

    return copie;
}
