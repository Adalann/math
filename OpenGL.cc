/*********************************************************/
/*                    openGL.cc                          */
/*********************************************************/
/*                                                       */
/*********************************************************/ 

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
#include "FractionRationnelle.h"
#include "PointMassique.h"
#include "Bernstein.h"
#include "Casteljau.h"
#include "Segment.h"
#include "Dessin.h"

using namespace std;

float Scal = 17;

float trX = 0.0, trY = 0.0, dist = 17.; //,trZ=0.0
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
void menu(Polynome &numerateur, Polynome &denominateur);

//-************************************************************
//
//  Procedure avec mise en file des sommets des primitives
//
//-***********************************************************
void init(Polynome &numerateur, Polynome &denominateur);

int main(int argc, char **argv)
{
    Polynome numerateur;
    Polynome denominateur;

    menu(numerateur, denominateur);

    /* initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Lanvin Martos");
    /* Initialisation d'OpenGL */

    time_t now = time(0);
    tm * ltm = localtime(&now);
    if (ltm->tm_hour < 9 || ltm->tm_hour >= 17)
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
    init(numerateur, denominateur);
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
    if(dist > 1)
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

void reshape(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //taille de la scene
    float Ortho = -300;
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
        yRightOld = y;
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
 **                    Affichage de  la scene                  **
 **                                                            **
 ****************************************************************/

//fonction ou les objets sont a definir
void init(Polynome &numerateur, Polynome &denominateur)
{ 
    Point O(0., 0.), I(1., 0.), J(0., 1.);
    Segment abscisse(-1000000, 0, 1000000, 0), ordonnee(0, -1000000, 0, 1000000);

    FractionRationnelle F(numerateur, denominateur);

    glNewList(1, GL_COMPILE_AND_EXECUTE); //liste numero 1
        trace_point(O, 0., 0., 1., 15.);  //O
        trace_point(I, 1., 0., 0., 10.);  //I
        trace_point(J, 0., 0.5, 0., 10.); //J
        trace_segment(O, I, 1.0, 0.0, 1.0, 2.0);  // on trace [OI]
        trace_segment(O, J, 1.0, 0.5, 0.0, 2.0);  // on trace [OJ]
        trace_segment(abscisse, 0., 0., 0., 0.5); // on trace l'axe des abcsisse
        trace_segment(ordonnee, 0., 0., 0., 0.5); // on trace l'axe des ordonnees
        for(int i = -100; i <= 100; i++) // boucle pour les graduations
        {
            trace_segment(i, -0.25, i, 0.25, (i % 10 == 0 ? 255. : 0.), 0., 0., 0.3);
            trace_segment(-0.25, i, 0.25, i, (i % 10 == 0 ? 255. : 0.), 0., 0., 0.3);
        }
    glEndList();

    glNewList(2, GL_COMPILE_AND_EXECUTE); //liste numero 2
        F.trace_assymptotes();
        F.trace_courbe();
    glEndList();

    glNewList(3, GL_COMPILE_AND_EXECUTE); //liste numero 3
        F.changement_homographique();
    glEndList();

    cout << "\nFin !" << endl;
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
    glFlush();
    // On echange les buffers
    glutSwapBuffers();
}

void menu(Polynome &numerateur, Polynome &denominateur)
{
    cout << "========= Affichage de fractions rationnelles à l'aide de courbes de Bézier =========" << endl;

    cout << "\n\n";
    cout << "1.\tf(x) = (2x² - 1) / (x² + 2x - 3)" << endl;
    cout << "2.\tf(x) = (x³ - 4x² - 11x + 16) / (x² + 2x - 3)" << endl;
    cout << "3.\tf(x) = (x² - x - 1) / (2x - 3)" << endl;
    cout << "4.\tf(x) = x²" << endl;
    cout << "5.\tEntrer les coefficients" << endl;
    cout << "6.\tQuitter le programme" << endl;
    cout << "\n\n";

    int input(0);
    float coef(0);
    vector<float> num;
    vector<float> denom;

    do {
        cin >> input;
        switch (input)
        {
            case 1:
                numerateur = Polynome(vector<float>({2, 0, -1}));
                denominateur = Polynome(vector<float>({1, 2, -3}));
                break;
            case 2:
                numerateur = Polynome(vector<float>({1, -4, -11, 16}));
                denominateur = Polynome(vector<float>({1, 2, -3}));
                break;
            case 3:
                numerateur = Polynome(vector<float>({1, -1, -1}));
                denominateur = Polynome(vector<float>({2, -3}));
                break;
            case 4:
                numerateur = Polynome(vector<float>({1, 0, 0}));
                denominateur = Polynome(vector<float>({1}));
                break;
            case 5:
                cout << "Entrez les coeficients tels que l'on ai :  f(x) = (ax³ + bx² + cx + d) / (ex² + fx + g)" << endl;
                for(char i = 97; i < 104; i++)
                {
                    cout << i << " : ";
                    cin >> coef;
                    if(i < 101)
                        num.push_back(coef);
                    else
                        denom.push_back(coef);
                }
                numerateur = Polynome(num);
                numerateur.normalize();
                denominateur = Polynome(denom);
                denominateur.normalize();
                break;
        }
    } while (input < 0 && input > 5);
}
