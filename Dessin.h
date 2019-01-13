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
void trace_point(float x, float y, float red, float green, float blue, float size);

// Trace un point à partir d'un objet Point
void trace_point(Point p, float red, float green, float blue, float size);

// Trace un segement à partir des coordonnées des points
void trace_segment(float x0, float y0, float x1, float y1, float red, float green, float blue, float size);

// Trace un segment à partir de deux objets points
void trace_segment(Point p0, Point p1, float red, float green, float blue, float size);

// Trace un segment à partir d'un objet segment
void trace_segment(Segment s, float red, float green, float blue, float size);