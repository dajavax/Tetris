// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>

void init()
{
}

void createList()
{
}
void display()
{
}

void myTimer( int valor)
{
}

void reshape(int ancho, int alto)
{
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
}
void special(int c, int x, int y){
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE );
    glutCreateWindow("Tetris");
    init();    
    createList();
    glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(special);
    glutReshapeFunc(reshape);
	glutTimerFunc(16,myTimer,1);
    glutMainLoop();
    return 0;
}

