/*********************************************************/
/*                    openGL.cc                          */
/*********************************************************/
/*                                                       */
/*********************************************************/ 

// mesalib freeglut mesaglu

/* inclusion des fichiers d'en-tete Glut */
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <jpeglib.h>
#include <jerror.h>
#define Pi 3.141592654

#include <vector>
#include "Test.cc"
#include "Point.h"
#include "Segment.h"
#include "Polynome.h"

using namespace std;

double Scal = 0.1;

double trX = 0.0, trY = 0.0, dist = 0.; //,trZ=0.0
char pressRight, pressLeft;
int anglex, angley, xLeft, yLeft, xLeftOld, yLeftOld;
int xRight, yRight, xRightOld, yRightOld;

/* Prototype des fonctions */
void affichage();//  procedure a modifier en fonction de la scene
void clavier(unsigned char touche, int x, int y); 
void reshape(int x, int y);
void idle();
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);

//-************************************************************
//
//  Procedure avec mise en file des sommets des primitives
//
//-***********************************************************
void init();

int main(int argc, char **argv)
{
    /* initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("RQBC et conique.");
    /* Initialisation d'OpenGL */
    time_t now = time(0);
    tm * ltm = localtime(&now);
    cout << ltm->tm_hour << endl;
    if (ltm->tm_hour < 8 || ltm->tm_hour >= 19)
        glClearColor(0.5, 0.5, 0.5, 0.0);
    else
        glClearColor(1.0, 1.0, 1.0, 0.0);
        
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);


    glColor3f(0.0, 0.0, 0.0);
    //glEdgeFlag(GL_FALSE);
    glEdgeFlag(GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    // glEnable(GL_LIGHTING);
    glDisable(GL_LIGHTING);


    /* enregistrement des fonctions de rappel */
    init();
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

/****************************************************************
 **                                                            **
 **                   Fonctions de callback                    **
 **                                                            **
 ****************************************************************/

void zoomIn()
{
    if(dist < 149)
    {
        dist += 0.5;
        Scal += 0.5;
    }
    glutPostRedisplay();
}

void zoomOut()
{
    if(dist >= 0.5)
    {
        dist -= 0.5;
        Scal -= 0.5;
    }
    glutPostRedisplay();
}

void clavier(unsigned char touche, int x, int y)
{
    switch (touche)
    {
        case 'q' : /*la touche 'q' permet de quitter le programme */
        case 'Q' : exit(0);
        case '+' : zoomOut(); break;
        case '-' : zoomIn();  break;
        case '6' : trX -= 0.25;  glutPostRedisplay();  break;
        case '4' : trX += 0.25;  glutPostRedisplay();  break;
        case '8' : trY += 0.25;  glutPostRedisplay();  break;
        case '2' : trY -= 0.25;  glutPostRedisplay();  break;
        case '0' : trX = 0.; trY = 0.; anglex = 0.; angley = 0.; glutPostRedisplay(); break;
    }
}

void reshape(int x,int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //taille de la scene
    double Ortho = -300;
    glOrtho(-Ortho, Ortho, -Ortho, Ortho, -Ortho, Ortho); // fenetre
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

void mouse(int button, int state,int x,int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
            {
                pressLeft = 1;
                xLeftOld = x;
                yLeftOld = y;
            }
            else if(state == GLUT_UP)
                pressLeft = 0;
            break;
        case GLUT_RIGHT_BUTTON:
        {
            if(state == GLUT_DOWN)
            {
                pressRight = 1; /* le booleen presse passe a 1 (vrai) */
                xRightOld = x;  /* on sauvegarde la position de la souris */
                xRightOld = y;
            }
            else if(state == GLUT_UP)
                pressRight = 0;
            break;
        }
        case 3: zoomIn();  break;
        case 4: zoomOut(); break;
    }
}

void mousemotion(int x, int y)
{
    if (pressRight) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
        en fonction de la position actuelle de la souris et de la derniere
        position sauvegardee */
        anglex = anglex + (x - xRightOld);
        angley = angley + (y - yRightOld);
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
        xRightOld = x;       /* sauvegarde des valeurs courante de le position de la souris */
        xRightOld = y;
    }
    else if (pressLeft)
    {
        trX -= (x - xLeftOld) * 1 / Scal * 0.08;
        trY -= (y - yLeftOld) * 1 / Scal * 0.08;
        glutPostRedisplay();
        xLeftOld = x; /* sauvegarde des valeurs courante de le position de la souris */
        yLeftOld = y;
    } 
}


/****************************************************************
 **                                                            **
 **                    Fonctions de tracé                      **
 **                                                            **
 ****************************************************************/

// Trace un point à partir de coordonnées
void trace_point(double x, double y, double red, double green, double blue, double size)
{
    glColor3f(red, green, blue); // initialisation de la couleur
	glPointSize(size);	         // initialisation de la taille
	glBegin(GL_POINTS);	         // on trace un point
	    glVertex2f(x,y);         // coordonnees du point
	glEnd();	                 // fin de glBegin
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
	    glVertex2f(x0, y0);       // coordonnees du premier point
        glVertex2f(x1, y1);   // coordonnees du dernier point 
	glEnd();                     // fin de glBegin
}

// Trace un segment à partir de deux objets points
void trace_segment(Point p0, Point p1, double red, double green, double blue, double size)
{
    trace_segment(p0.getX(), p0.getY(), p1.getX(), p1.getY(), red, green, blue, size);
}

// Trace 
void trace_segment(Segment s, double red, double green, double blue, double size)
{
    trace_segment(s.getA(), s.getB(), red, green, blue, size);
}

/****************************************************************
 **                                                            **
 **                    Affichage de  la scene                  **
 **                                                            **
 ****************************************************************/

//fonction ou les objets sont a definir
void init()
{ 
    Point O(0., 0.), I(1., 0.), J(0., 1.);
    Segment abscisse(-1000000, 0, 1000000, 0), ordonnee(0, -1000000, 0, 1000000);
    vector<Point> points1;
    vector<Point> points2;
    double const limit = -1000;
    double i = limit;
    while(i < -limit)
    {
        points1.push_back(polynome1(i));
        points2.push_back(polynome2(i));
        i += 0.1;
    }
    double num[4];
    num[0] = 0;
    num[1] = 2;
    num[2] = 0;
    num[3] = -1;
    double denom[4];
    denom[0] = 0;
    denom[1] = 0;
    denom[2] = 2;
    denom[3] = -3;

    Polynome p(num, denom);
    cout << p.to_s() << endl;
    double X1(0), X2(0);

    p.solve_denom(X1, X2);
    cout << "X1 : " << X1 << " X2 : " << X2 << endl;

    
    glNewList(1, GL_COMPILE_AND_EXECUTE); //liste numero 1
        trace_point(O, 0., 0., 1., 15.);  //O
        trace_point(I, 1., 0., 0., 10.);  //I
        trace_point(J, 0., 0.5, 0., 10.); //J
        trace_segment(O, I, 1.0, 0.0, 1.0, 2.0);  // on trace [OI]
        trace_segment(O, J, 1.0, 0.50, 0.0, 2.0); // on trace [OJ]
        trace_segment(abscisse, 0., 0., 0., 0.5); // on trace l'axe des abcsisse
        trace_segment(ordonnee, 0., 0., 0., 0.5); // on trace l'axe des ordonnees
    glEndList();

    glNewList(2, GL_COMPILE_AND_EXECUTE); //liste numero 2
        // for (int i = 0; i < points2.size() - 1; i++)
        // {
        //     trace_point(points2[i], 0, 1, 0, 7);
        //     trace_segment(points2[i], points2[i + 1], 0, 1, 0., 2.0);
        // }
    glEndList();

    glNewList(3, GL_COMPILE_AND_EXECUTE); //liste numero 4
        // for(int i = 0; i < points1.size() - 1; i++)
        // {
        //     trace_point(points1[i], 0, 0, 1, 7);
        //     trace_segment(points1[i], points1[i + 1], 0., 0., 1., 2.0);
        // }
    glEndList();

    glNewList(4, GL_COMPILE_AND_EXECUTE);  //liste numero 5

    glEndList();

    glNewList(5, GL_COMPILE_AND_EXECUTE); //liste numero 6
        
    glEndList();


    cout << "\nDone." << endl;
}
   
// fonction permettant d'afficher les objets en utilisant des listes   
void affichage() 
{
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, dist);
    // Pour la 3D
    // glRotatef(-angley,1.0,0.0,0.0);
    // glRotatef(-anglex,0.0,1.0,0.0);
    // Pour la 2D    
    glRotatef(-anglex + angley, 0.0, 0.0, 1.0);
    glScalef(Scal, Scal, Scal); // diminution de la vue de la scene
    glRotatef(180, 0.0, 1.0, 0.0);
    glRotatef(180, 1.0, 0.0, 0.0);
    glTranslatef(-trX, trY, 0.);
        glCallList(1); // appel de la liste numero 1
        glCallList(2);   // appel de la liste numero 2
        glCallList(3);   // appel de la liste numero 3
        glCallList(4);   // appel de la liste numero 4
        glCallList(5);   // appel de la liste numero 4
    glFlush(); 
    // On echange les buffers
    glutSwapBuffers();
}
