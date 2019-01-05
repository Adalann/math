#include "Point.h"
#include <iostream>

using namespace std;

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

void Point::print(string comment) const
{
    cout << comment << " x = " << x << ", y = " << y << endl;
}

void Point::trace(double taille, double r, double g, double b) const
{
    glColor3f(r, g, b);   // initialisation de la couleur
    glPointSize(taille);  // initialisation de la taille
    glBegin(GL_POINTS);   // on trace un point
    glVertex2f(x, y);     // coordonnees du point
    glEnd();
}