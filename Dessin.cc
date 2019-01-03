#include "Dessin.h"
#include <vector>

using namespace std;

/****************************************************************
 **                                                            **
 **                    Fonctions de tracé                      **
 **                                                            **
 ****************************************************************/

// Trace un point à partir de coordonnées
void trace_point(double x, double y, double red, double green, double blue, double size)
{
    glColor3f(red, green, blue); // initialisation de la couleur
    glPointSize(size);           // initialisation de la taille
    glBegin(GL_POINTS);          // on trace un point
    glVertex2f(x, y);            // coordonnees du point
    glEnd();                     // fin de glBegin
}

// Trace un point à partir d'un objet Point
void trace_point(Point p, double red, double green, double blue, double size)
{
    trace_point(p.getX(), p.getY(), red, green, blue, size);
}

// Trace un segement à partir des coordonnées des points
void trace_segment(double x0, double y0, double x1, double y1, double red, double green, double blue, double size)
{
    glColor3f(red, green, blue); // initialisation de la couleur
    glLineWidth(size);           // initialisation de la taille
    glBegin(GL_LINES);           // on trace un segment
    glVertex2f(x0, y0);          // coordonnees du premier point
    glVertex2f(x1, y1);          // coordonnees du dernier point
    glEnd();                     // fin de glBegin
}

// Trace un segment à partir de deux objets points
void trace_segment(Point p0, Point p1, double red, double green, double blue, double size)
{
    trace_segment(p0.getX(), p0.getY(), p1.getX(), p1.getY(), red, green, blue, size);
}

// Trace un segment à partir d'un objet segment
void trace_segment(Segment s, double red, double green, double blue, double size)
{
    trace_segment(s.getA(), s.getB(), red, green, blue, size);
}