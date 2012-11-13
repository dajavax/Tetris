// Tetris.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
int borx = 80.0;
int bory = 260.0;
double movX = -80;
double movY = 240;
int figura, rotacion = 0;
double cuboVertices[9][2] = {{0.0,0.0},{20.0,0.0},{20.0,20.0},{0.0,20.0},{-20.0,20.0},{-20.0,0.0},{-20.0,-20.0},{0.0,-20.0},{20.0,-20.0}};
double paloVertices[10][2] = {{0.0,0.0},{0.0,-20.0},{0.0,-40.0},{20.0,-40.0},{20.0,-20.0},{20.0,0.0},{20.0,20.0},{20.0,40.0},{0.0,40.0},{0.0,20.0}};
double eleVertices[12][2] = {{0.0,0.0},{0.0,-20.0},{0.0,-40.0},{20.0,-40.0},{20.0,-20.0},{20.0,0.0},{20.0,20.0},{20.0,40.0},{0.0,40.0},{0.0,20.0},{40.0,-40.0},{40.0,-20.0}};
int cuadroCubo[4][4] ={{0,1,2,3},{5,0,3,4},{6,7,0,5},{7,8,1,0}};
int cuadroPalo[4][4] ={{9,6,7,8},{0,5,6,9},{1,4,5,0},{2,3,4,1}};
int cuadroEle[5][4] ={{9,6,7,8},{0,5,6,9},{1,4,5,0},{2,3,4,1},{3,10,11,4}};

void init(void)
{
    srand(time(NULL));
        //crea el random de las figuras inicial
     switch (rand()%3+1) {
        case 1: //cubo
            figura = 1;
            break;
        case 2://Palo
            figura = 2;
            break;
        case 3://ele
            figura = 3;
            break;
    }
    glClearColor (0.0, 0.0, 0.0, 0.0);
    //glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity ();

}
//funcion que despliega los bordes
void borders(){
     //cuadro exterior
    glColor3f(0.5, 0.5, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(borx+10,-bory-10,0.0);
	glVertex3f(borx+10,bory+10,0.0);
	glVertex3f(-bory-10,bory+10,0.0);
	glVertex3f(-bory-10,-bory-10,0.0);;
	glEnd();
    //el cuadro interior
    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(borx,-bory,0.0);
	glVertex3f(borx,bory,0.0);
	glVertex3f(-bory,bory,0.0);
	glVertex3f(-bory,-bory,0.0);
	glEnd();
}
void cubo(){
	glPushMatrix();
	glTranslatef(movX,movY,0);
	glRotatef(rotacion, 0, 0, 1);
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    for (int i=0; i<4; i++) {
        glVertex2dv(cuboVertices[cuadroCubo[i][0]]);
        glVertex2dv(cuboVertices[cuadroCubo[i][1]]);
        glVertex2dv(cuboVertices[cuadroCubo[i][2]]);
        glVertex2dv(cuboVertices[cuadroCubo[i][3]]);
    }
    glEnd();
    glColor3f(0, 0, 0);
	 glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2dv(cuboVertices[3]);
        glVertex2dv(cuboVertices[7]);
        glVertex2dv(cuboVertices[5]);
        glVertex2dv(cuboVertices[1]);
    glEnd();
    glPopMatrix();
}
 void palo(){
    glPushMatrix();
	glTranslatef(movX,movY,0);
	glRotatef(rotacion, 0, 0, 1);
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    for (int i=0; i<4; i++) {
        glVertex2dv(paloVertices[cuadroPalo[i][0]]);
        glVertex2dv(paloVertices[cuadroPalo[i][1]]);
        glVertex2dv(paloVertices[cuadroPalo[i][2]]);
        glVertex2dv(paloVertices[cuadroPalo[i][3]]);
    }
    glEnd();
    glColor3f(0, 0, 0);
	 glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2dv(paloVertices[9]);
        glVertex2dv(paloVertices[6]);
        glVertex2dv(paloVertices[0]);
        glVertex2dv(paloVertices[5]);
        glVertex2dv(paloVertices[1]);
        glVertex2dv(paloVertices[4]);

    glEnd();
    glPopMatrix();
 }
 void ele(){
     glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(0, 0, 1);
        glBegin(GL_QUADS);
        for (int i=0; i<5; i++) {
            glVertex2dv(eleVertices[cuadroEle[i][0]]);
            glVertex2dv(eleVertices[cuadroEle[i][1]]);
            glVertex2dv(eleVertices[cuadroEle[i][2]]);
            glVertex2dv(eleVertices[cuadroEle[i][3]]);
        }
        glEnd();
        glColor3f(0, 0, 0);
         glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2dv(eleVertices[9]);
            glVertex2dv(eleVertices[6]);
            glVertex2dv(eleVertices[0]);
            glVertex2dv(eleVertices[5]);
            glVertex2dv(eleVertices[1]);
            glVertex2dv(eleVertices[4]);
            glVertex2dv(eleVertices[4]);
            glVertex2dv(eleVertices[3]);
            glVertex2dv(eleVertices[4]);
            glVertex2dv(eleVertices[11]);
        glEnd();
        glPopMatrix();
 }
 void figuraActual(int numero){
     switch (numero) {
        case 1:
            cubo();
            break;
        case 2:
            palo();
            break;
        case 3:
            ele();
            break;
        default:
            break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    borders();
    figuraActual(figura);
    glutSwapBuffers();
	//glMatrixMode(GL_MODELVIEW);
}

void myTimer( int valor)
{
    movY = movY - 2;
    glutPostRedisplay();
    glutTimerFunc(100, myTimer,1);
}

void reshape(int w, int h)
{
      glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-280.0, 280, -280, 280, -280, 280);//izq, der, abajo, arriba, cerca
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);//ajuste el tamaño de la ventana
    //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
     glLoadIdentity ();

}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
}
void special(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
                movX=movX-20;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
                movX=movX+20;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            movY=movY-4;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            rotacion+=90;
            glutPostRedisplay();
            break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(640,680);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Tetris");
    init();
    //createList();
    glutDisplayFunc(display);
	//glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(special);
    glutReshapeFunc(reshape);
	glutTimerFunc(100,myTimer,1);
    glutMainLoop();
    return 0;
}

