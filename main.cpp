// Tetris.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
int borx = 90.0;
int borx2 = 270.0;
int bory = 560.0;
double movX = -80;
double movY = 550;
int figura, rotacion = 0;


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
	glVertex3f(borx+10,-10,0.0);
	glVertex3f(borx+10,bory+10,0.0);
	glVertex3f(-borx2-10,bory+10,0.0);
	glVertex3f(-borx2-10,-10,0.0);
	glEnd();
    //el cuadro interior
    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(borx,0,0.0);
	glVertex3f(borx,bory,0.0);
	glVertex3f(-borx2,bory,0.0);
	glVertex3f(-borx2,0,0.0);
	glEnd();
}
//para que marque la separación entre lo cubos
void cuadricula(){
    //lineas verticuales
    glColor3f(0, 0, 0);
	 glLineWidth(2);
	glBegin(GL_LINES);
	for (double x=-290.0; x<=90; x=x+20){
		glVertex2d(x,0);
		glVertex2d(x,560);
	}
	glEnd();
	//lineas horizontales
	glBegin(GL_LINES);
	for (double y=0.0; y<=560; y=y+20){
		glVertex2d(-270,y);
		glVertex2d(90,y);
	}
	glEnd();
}
void ele(){
    glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(0, 0, 1);
        glPushMatrix();
            glTranslatef(0,0,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,-20,0);
            glutSolidCube(20);
        glPopMatrix();
    glPopMatrix();

}
 void cubo(){
    glPushMatrix();
        glTranslatef(movX,movY,0);
        //glRotatef(rotacion, 0, 0, 1);
        glColor3f(1, 0, 0);
        glPushMatrix();
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,0,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,-20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
            glutSolidCube(20);
        glPopMatrix();
    glPopMatrix();
 }
 void palo(){
     glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(0, 1, 0);
        glPushMatrix();
            glTranslatef(0,0,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-40,0);
            glutSolidCube(20);
        glPopMatrix();
    glPopMatrix();
 }
 void te(){
      glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(1, 1, 0);
        glPushMatrix();
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,0,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,0,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
            glutSolidCube(20);
        glPopMatrix();
    glPopMatrix();
 }
 void ese(){
    glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(.62, .12, .94);
        glPushMatrix();
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,0,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,-20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
            glutSolidCube(20);
        glPopMatrix();
    glPopMatrix();
 }
 void zeta(){
    glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(0, 1, .60);
        glPushMatrix();
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,20,0);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,0,0);
            glutSolidCube(20);
        glPopMatrix();
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
    zeta();
    //figuraActual(figura);
    cuadricula();
    glutSwapBuffers();
	//glMatrixMode(GL_MODELVIEW);
}
void myTimer( int valor)
{
    movY = movY - 20;
    glutPostRedisplay();
    glutTimerFunc(500, myTimer,1);
}

void reshape(int w, int h)
{
      glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-290.0, 290, -20, 580, -290, 290);//izq, der, abajo, arriba, cerca
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
            if(movX >= -220){
                movX=movX-20;
                glutPostRedisplay();

                }
                break;
        case GLUT_KEY_RIGHT:
            if(movX <= 40){
                movX=movX+20;
            glutPostRedisplay();
            }
            break;
        case GLUT_KEY_DOWN:
            movY=movY-20;
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
	glutTimerFunc(500,myTimer,1);
    glutMainLoop();
    return 0;
}

