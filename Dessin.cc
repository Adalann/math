#include "Dessin.h"

using namespace std;

/****************************************************************
 **                                                            **
 **                    Fonctions de tracé                      **
 **                                                            **
 ****************************************************************/

// Trace un point à partir de coordonnées
void trace_point(float x, float y, float red, float green, float blue, float size)
{
    glColor3f(red, green, blue); // initialisation de la couleur
    glPointSize(size);           // initialisation de la taille
    glBegin(GL_POINTS);          // on trace un point
    glVertex2f(x, y);            // coordonnees du point
    glEnd();                     // fin de glBegin
}

// Trace un point à partir d'un objet Point
void trace_point(Point p, float red, float green, float blue, float size)
{
    trace_point(p.getX(), p.getY(), red, green, blue, size);
}

// Trace un segement à partir des coordonnées des points
void trace_segment(float x0, float y0, float x1, float y1, float red, float green, float blue, float size)
{
    glColor3f(red, green, blue); // initialisation de la couleur
    glLineWidth(size);           // initialisation de la taille
    glBegin(GL_LINES);           // on trace un segment
    glVertex2f(x0, y0);          // coordonnees du premier point
    glVertex2f(x1, y1);          // coordonnees du dernier point
    glEnd();                     // fin de glBegin
}

// Trace un segment à partir de deux objets points
void trace_segment(Point p0, Point p1, float red, float green, float blue, float size)
{
    trace_segment(p0.getX(), p0.getY(), p1.getX(), p1.getY(), red, green, blue, size);
}

// Trace un segment à partir d'un objet segment
void trace_segment(Segment s, float red, float green, float blue, float size)
{
    trace_segment(s.getA(), s.getB(), red, green, blue, size);
}

void trace_courbe_bezier(vector<PointMassique> points)
{
    int degre_max = points.size() - 1;
    Point old_point;

    for (float t = 0.001; t < 1; t += 0.001)
    {
        double denom = 0;
        for (int i = 0; i < points.size(); i++)
            denom += points[i].getW() * bernstein(degre_max, i, t);
        if (denom == 0)
            ;
        else
        {
            double x(0), y(0);
            for (int i = 0; i < points.size(); i++)
            {
                if (points[i].getW() != 0)
                {
                    x += points[i].getW() * bernstein(degre_max, i, t) * points[i].getX();
                    y += points[i].getW() * bernstein(degre_max, i, t) * points[i].getY();
                }
                else
                {
                    x += bernstein(degre_max, i, t) * points[i].getX();
                    y += bernstein(degre_max, i, t) * points[i].getY();
                }
            }

            Point new_point(x / denom, y / denom);
            trace_point(new_point, 0, 0, 255, 2);
            old_point = new_point;
        }
    }
}