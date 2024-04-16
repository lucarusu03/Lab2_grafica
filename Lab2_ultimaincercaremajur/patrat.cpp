#include "GLOS.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include <math.h>

static GLfloat x = 0;
static GLfloat z = 0;
static GLfloat radius = 10;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 40;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(x, 0.4, 0.1, 0);

    glBegin(GL_QUAD_STRIP);
    {
        glColor3f(1, 0, 1);

        for (int i = 0; i <= 360; i++) {
            float alpha = ((2 * 3.14) / 360) * i;
            x = cos(alpha) * radius;
            z = sin(alpha) * radius;
            glColor3f(0, 0, 1);
            glVertex3f(x, -40, z);
            glColor3f(1, 0, 0);
            glVertex3f(x, 40, z);


        }




    }
    glEnd();

    glFlush();
}

#define ISOTROPIC
#ifdef ISOTROPIC

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Un patrat");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
