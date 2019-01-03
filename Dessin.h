#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include "Point.h"
#include "Segment.h"

/****************************************************************
 **                                                            **
 **                    Fonctions de tracé                      **
 **                                                            **
 ****************************************************************/

// Trace un point à partir de coordonnées
void trace_point(double x, double y, double red, double green, double blue, double size);

// Trace un point à partir d'un objet Point
void trace_point(Point p, double red, double green, double blue, double size);

// Trace un segement à partir des coordonnées des points
void trace_segment(double x0, double y0, double x1, double y1, double red, double green, double blue, double size);

// Trace un segment à partir de deux objets points
void trace_segment(Point p0, Point p1, double red, double green, double blue, double size);

// Trace un segment à partir d'un objet segment
void trace_segment(Segment s, double red, double green, double blue, double size);