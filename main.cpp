// Tetris.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "imageloader.h"

int borx = 360.0;
int bory = 560.0;
int matriz[29][18];
int tetromino[4][2];
int inicioV = 0;
int movX, movY, movXant, movYant, bajo;
int avance = 0;
int pausaV = 0;
char msg[50];
int tocaPiso;
int mensaje;//apuntadore de la lista
int figura, rotacion = 0, rotacionant=0, rapidez;
static GLuint texName[36];
const int TEXTURE_COUNT=6;
int score = 0;
float light_ambient [] = {0.0,0.2,0.0,1.0};
float light_diffuse_specular [] = {0.8,0.8,0.8,1.0};
float light_pos [] = {0.0,0.0,5.0,1.0};
float spot_dir [] = {0.0,0.0,-1.0};
float spot_cutoff = 30.0;
float spot_exponent = 1.0;
float focus_emission [] = {0.8,0.8,0.8,1.0};
void updateAnteriores(){
	rotacionant=rotacion;
	movXant=movX;
	movYant=movY;
}
//Luz ambiente
GLfloat mat_ambient2[][4] = {
    {0.0215, 0.1745, 0.0215,1.0},
    {0.135, 0.2225, 0.1575,1.0},
    {0.05375, 0.05, 0.06625,1.0},
    {0.25, 0.20725, 0.20725,1.0},
    {0.1745, 0.01175, 0.01175,1.0},
    {0.1, 0.18725, 0.1745,1.0},
    {0.329412, 0.223529, 0.027451, 1.0},
    {0.2125, 0.1275, 0.054, 1.0},
    {0.25, 0.25, 0.25, 1.0},
    {0.19125, 0.0735, 0.0225, 1.0},
    {0.24725, 0.1995, 0.0745, 1.0},
    {0.19225, 0.19225, 0.19225, 1.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.1, 0.06},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.02, 0.02, 0.02,1.0},
    {0.0, 0.05, 0.05,1.0},
    {0.0, 0.05, 0.0,1.0},
    {0.05, 0.0, 0.0,1.0},
    {0.05, 0.05, 0.05,1.0},
    { 0.05, 0.05, 0.0,1.0}

};


//luz difusa
GLfloat mat_diffuse2[][4] = {
    {0.07568, 0.61424, 0.07568,1.0},
    {0.54, 0.89, 0.63,1.0},
    {0.18275, 0.17, 0.22525,1.0},
    {1, 0.829, 0.829,1.0},
    {0.61424, 0.04136, 0.04136, 1.0},
    {0.396, 0.74151, 0.69102,1.0},
    {0.780392, 0.568627, 0.113725, 1.0},
    {0.714, 0.4284, 0.18144, 1.0},
    {0.4, 0.4, 0.4, 1.0},
    {0.7038, 0.27048, 0.0828, 1.0},
    {0.75164, 0.60648, 0.22648, 1.0},
    {0.50754, 0.50754, 0.50754, 1.0},
    {0.01, 0.01, 0.01, 1.0},
    {0.0, 0.50980392, 0.50980392,1.0},
    {0.1, 0.35, 0.1, 1.0},
    {0.5, 0.0, 0.0,1.0},
    {0.55, 0.55, 0.55,1.0},
    {0.5, 0.5, 0.0,1.0},
    {0.01,0.01, 0.01, 1.0},
    {0.4, 0.5, 0.5, 1.0},
    { 0.4, 0.5, 0.4, 1.0},
    { 0.5, 0.4, 0.4, 1.0},
    {0.5, 0.5, 0.5, 1.0},
    {0.5, 0.5, 0.4, 1.0}
};

//especular
GLfloat mat_specular2[][4] = {
    {0.633,0.727811,0.633,1.0},
    {0.316228, 0.316228, 0.316228, 0.1},
    {0.332741, 0.328634, 0.346435,1.0},
    {0.296648, 0.296648, 0.296648,1.0},
    {0.727811, 0.626959, 0.626959,1.0},
    {0.297254, 0.30829, 0.306678,1.0},
    {0.992157, 0.941176, 0.807843, 1.0},
    {0.393548, 0.271906, 0.166721, 1.0},
    {0.774597, 0.774597, 0.774597, 1.0},
    {0.256777, 0.137622, 0.086014, 1.0},
    {0.628281, 0.555802, 0.366065, 1.0},
    {0.508273, 0.508273, 0.508273, 1.0},
    {0.50, 0.50, 0.50,1.0},
    {0.50196078, 0.50196078, 0.50196078, 1.0},
    {0.45, 0.55, 0.45, 1.0},
    {0.7, 0.6, 0.6, 1.0},
    {0.70, 0.70, 0.70, 1.0},
    {0.60, 0.60, 0.50,1.0},
    {0.4, 0.4, 0.4,1.0},
    { 0.04, 0.7, 0.7,1.0},
    {0.04, 0.7, 0.04,1.0},
    {0.7, 0.04, 0.04,1.0},
    {0.7, 0.7, 0.7,1.0},
    {0.7, 0.7, 0.04,1.0}
};

//brillo
GLfloat mat_shininess2[][1] = {
{0.6},{0.1},{0.3},{0.088}, {0.6},{0.1},
{ 0.21794872},{ 0.2},{ 0.6},{ 0.1},{ 0.4},{ 0.4},
{.25},{.25},{.25},{.25},{.25},{.25},
{0.078125},{.078125},{.078125},{.078125},{.078125},{.078125},{.078125}
};

int checarLimites(int x, int y){
	if(x<10){
		movX+=20;
		return true;
	}
	if(x>350){
		movX-=20;
		return true;
	}
	if((((y-10)/20)+1)<29&&matriz[((y-10)/20)+1][(x-10)/20]!=0){
		if(movYant>movY||tocaPiso>0)
			tocaPiso++;
		movY=movYant;
		movX=movXant;
		rotacion=rotacionant;
		return true;
	}
	return false;
}
void fijar(int x, int y){
	int fila=((y-10-bajo)/20)+1;
	matriz[fila][(x-10)/20]=figura;
	bool clear=true;
	for(int z=0; z<18&&clear; z++)
		clear=clear&&matriz[fila][z]!=0;
	if(clear){
		for(int i=fila+1; i<29; i++){
			for(int z=0; z<18; z++){
				matriz[i-1][z]=matriz[i][z];
			}
		}
		for(int z=0; z<18; z++){
			matriz[28][z]=0;
		}
		bajo+=20;
	}
}
void displayScore()
{
    glColor3f(1.0,1.0,1.0);
	glRasterPos2f(10.9,10.9);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)'S');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)'c');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)'o');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)'r');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)'e');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)':');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)' ');
	char string [4];
	itoa(score,string,10);
	for(int i=0; string[i]!='\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (GLubyte)string[i]);


}

void nuevaPieza(){
	rapidez=500;
	tocaPiso=0;
	bajo=0;
	switch (rand()%6+1) {
        case 1: //cubo
            figura = 1;
            break;
        case 2://Palo
            figura = 2;
            break;
        case 3://ele
            figura = 3;
            break;
        case 4://te
            figura = 4;
            break;
        case 5://ese
            figura = 5;
            break;
        case 6://zeta
            figura = 6;
            break;
	}
	movX = movXant = 170;
	movY = movYant = 550;
}
void init(void)
{
    srand(time(NULL));
        //crea el random de las figuras inicial
    nuevaPieza();
	memset(matriz, 0, sizeof(matriz[0][0]) * 18 * 29);
	for(int z=0; z<18; z++)
		matriz[0][z]=1;
    glClearColor (0.0, 0.0, 0.0, 0.0);
    //glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	   glEnable(GL_TEXTURE_2D);
	glLoadIdentity ();

}
//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data

}
void initRendering()
{     srand(time(NULL));

        //crea el random de las figuras inicial
    nuevaPieza();
	memset(matriz, 0, sizeof(matriz[0][0]) * 18 * 29);
	for(int z=0; z<18; z++)
		matriz[0][z]=1;
    glClearColor (0.0, 0.0, 0.0, 0.0);
    GLuint i=0;
       GLfloat ambientLight[] = {10.2f, 10.2f, 10.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat directedLight[] = {10.9f, 10.9f, 10.9f, 1.0f};
    GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); ///Users/mariaroque/Imagenes

    glEnable(GL_TEXTURE_2D);

    // glEnable(GL_COLOR_MATERIAL);
    glGenTextures(36, texName); //Make room for our texture
    Image* image;

image = loadBMP("/Users/Raul/Desktop/Tetris/img/fondo.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/negro.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/celeste.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/azul.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/amarillo.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/verde.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/morado.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/rojo.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/ini.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/fin.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/Tetris/img/pausar.bmp");loadTexture(image,i++);
    delete image;
}
void inicio(){
    glBindTexture(GL_TEXTURE_2D, texName[8]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
         glTexCoord2f(1.0f, 0.0f);
        glVertex3f(560.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(560.0f, 560.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f, 560.0f, 0.0f);
        glEnd();
}
void Pausar(){
    glBindTexture(GL_TEXTURE_2D, texName[10]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(300.0f, 0.0f, 0.0f);
         glTexCoord2f(1.0f, 0.0f);
        glVertex3f(560.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(560.0f, 560.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(300.0f, 560.0f, 0.0f);
        glEnd();
}
void fin(){
    glBindTexture(GL_TEXTURE_2D, texName[9]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
         glTexCoord2f(1.0f, 0.0f);
        glVertex3f(560.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(560.0f, 560.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f, 560.0f, 0.0f);
        glEnd();
}
//funcion que despliega los bordes
void borders(){


     //cuadro exterior
   /* glColor3f(0.5, 0.5, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(borx+10,-10,0.0);
	glVertex3f(borx+10,bory+10,0.0);
	glVertex3f(-10,bory+10,0.0);
	glVertex3f(-10,-10,0.0);
	glEnd();
    //el cuadro interior
    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(borx,0,0.0);
	glVertex3f(borx,bory,0.0);
	glVertex3f(0,bory,0.0);
	glVertex3f(0,0,0.0);
	glEnd();*/
}

void procesaMenu(int val){
	if(val == 1){
		exit(0);
	} else if(val == 2){

	}else if(val == 3){
        if(avance == 0){
            avance = 20;
        }
        else{
            avance = 0;
        }
	}
	glutPostRedisplay();
}

void addMenues(){
	int mainMenu, subMenu1, subMenu2, subMenu3,subMenu4;
	mainMenu = glutCreateMenu(procesaMenu);

	glutSetMenu(mainMenu);

	glutAddMenuEntry("Terminar Juego", 1);
	glutAddMenuEntry("Iniciar Otro", 2);
	glutAddMenuEntry("Pausar", 3);
	glutSetMenu(mainMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//para que marque la separación entre lo cubos
void cuadricula(){
    displayScore();
    //lineas verticuales
    glColor3f(1, 1, 0);
	 glLineWidth(2);
	glBegin(GL_LINES);
	for (double x=0.0; x<=360; x=x+20){
		glVertex2d(x,0);
		glVertex2d(x,560);
	}
	glEnd();
	//lineas horizontales
	glBegin(GL_LINES);
	for (double y=0.0; y<=560; y=y+20){
		glVertex2d(0,y);
		glVertex2d(360,y);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texName[0]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-20.0f, -20.0f, 0.0f);
         glTexCoord2f(1.0f, 0.0f);
        glVertex3f(580.0f, -20.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(580.0f, 580.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-20.0f, 580.0f, 0.0f);
        glEnd();
}
void ele(){
	int mat[4][4];
    glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(0, 0, 1);
        glPushMatrix();
            glTranslatef(0,0,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ele();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ele();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ele();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,-20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ele();
				return;
			}
        glPopMatrix();
    glPopMatrix();
	if(tocaPiso>1){
		nuevaPieza();
	} else {
		glPushMatrix();
			glTranslatef(movX,movY,0);
			glRotatef(rotacion, 0, 0, 1);
			glColor3f(0, 0, 1);
			glPushMatrix();
				glTranslatef(0,0,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[3]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[3]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[3]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(20,-20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[3]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
		glPopMatrix();
	}
}
 void cubo(){
	int mat[4][4];
    glPushMatrix();
        glTranslatef(movX,movY,0);
        glColor3f(1, 0, 0);
        glPushMatrix();
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				cubo();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,0,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				cubo();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,-20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				cubo();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				cubo();
				return;
			}
        glPopMatrix();
    glPopMatrix();
	if(tocaPiso>1){
		nuevaPieza();
	} else {
		glPushMatrix();
			glTranslatef(movX,movY,0);
			glColor3f(1, 0, 0);
			glPushMatrix();
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[4]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-20,0,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[4]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-20,-20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[4]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[4]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);			glPopMatrix();
		glPopMatrix();
	}
 }
 void palo(){
	 int mat[4][4];
     glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(0, 1, 0);
        glPushMatrix();
            glTranslatef(0,0,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				palo();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				palo();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				palo();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-40,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				palo();
				return;
			}
        glPopMatrix();
    glPopMatrix();
	if(tocaPiso>1){
		nuevaPieza();
	} else {
		 glPushMatrix();
			glTranslatef(movX,movY,0);
			glRotatef(rotacion, 0, 0, 1);
			glColor3f(0, 1, 0);
			glPushMatrix();
				glTranslatef(0,0,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[2]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);


			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[2]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[2]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-40,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[2]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
		glPopMatrix();
	}
 }
 void te(){
	 int mat[4][4];
      glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(1, 1, 0);
        glPushMatrix();
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				te();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,0,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				te();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,0,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				te();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				te();
				return;
			}
        glPopMatrix();
    glPopMatrix();
	if(tocaPiso>1){
		nuevaPieza();
	} else {
		  glPushMatrix();
			glTranslatef(movX,movY,0);
			glRotatef(rotacion, 0, 0, 1);
			glColor3f(1, 1, 0);
			glPushMatrix();
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[6]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-20,0,0);
glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[6]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);			glPopMatrix();
			glPushMatrix();
				glTranslatef(20,0,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[6]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[6]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
		glPopMatrix();
	}
 }
 void ese(){
	int mat[4][4];
    glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(.62, .12, .94);
        glPushMatrix();
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ese();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,0,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ese();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,-20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ese();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				ese();
				return;
			}
        glPopMatrix();
    glPopMatrix();
	if(tocaPiso>1){
		nuevaPieza();
	} else {
		glPushMatrix();
			glTranslatef(movX,movY,0);
			glRotatef(rotacion, 0, 0, 1);
			glColor3f(.62, .12, .94);
			glPushMatrix();
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[5]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(20,0,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[5]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-20,-20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[5]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[5]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
		glPopMatrix();
	}
 }
 void zeta(){
	 int mat[4][4];
    glPushMatrix();
        glTranslatef(movX,movY,0);
        glRotatef(rotacion, 0, 0, 1);
        glColor3f(0, 1, .60);
        glPushMatrix();
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				zeta();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				zeta();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20,20,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				zeta();
				return;
			}
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20,0,0);
			glGetIntegerv(GL_MODELVIEW_MATRIX, &mat[0][0]);
			if(tocaPiso>1){
				fijar(mat[3][0], mat[3][1]);
			} else if(checarLimites(mat[3][0], mat[3][1])){
				glPopMatrix();
				glPopMatrix();
				zeta();
				return;
			}
        glPopMatrix();
    glPopMatrix();
	if(tocaPiso>1){
		nuevaPieza();
	} else {
		glPushMatrix();
			glTranslatef(movX,movY,0);
			glRotatef(rotacion, 0, 0, 1);
			glColor3f(0, 1, .60);
			glPushMatrix();

				 glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[7]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[7]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-20,20,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[7]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(20,0,0);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, texName[7]);
                glutSolidCube(18);
                glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
			glPopMatrix();
		glPopMatrix();
	}
 }
 void fijos(){
	 for(int i=1; i<29; i++){
		 for(int z=0; z<18; z++){
			 glPushMatrix();
			 bool cont=true;
			 switch(matriz[i][z]){
				case 1:
					glColor3f(1, 0, 0);
					break;
				case 2:
					glColor3f(0, 1, 0);
					break;
				case 3:
					glColor3f(0, 0, 1);
					break;
				case 4:
					glColor3f(1, 1, 0);
					break;
				case 5:
					glColor3f(.62, .12, .94);
					break;
				case 6:
					glColor3f(0, 1, .60);
					break;
				default:
					cont=false;
					break;
			 }
			 if(cont){
				 glTranslatef((z*20)+10,((i-1)*20)+10,0);
				 glutSolidCube(20);
			 }
			 glPopMatrix();
		 }
	 }
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
        case 4:
            te();
            break;
        case 5:
            ese();
            break;
        case 6:
            zeta();
            break;
        default:
            break;
    }
}

void lightSpot(){
glPushMatrix();
    glScaled(1, 1, 1);
    //glRotatef(-100.0,1.0,0.0,0.0);
    glTranslatef(10.0,0.0,0.0);
    //glRotatef(rot_angle_y,0.0,1.0,0.0);
    //glRotatef(rot_angle_x,1.0,0.0,0.0);
    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_dir);
    glTranslatef(light_pos[0],light_pos[1],light_pos[2]);
    //glTranslatef(trax*0.2,light_pos[1],tray*0.2);
    glColorMaterial(GL_FRONT,GL_EMISSION);
    glEnable(GL_COLOR_MATERIAL);
    glColor4fv(focus_emission);


}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //checa si esta pausado
    //lightSpot();


    if(pausaV == 1){
        Pausar();
    }//checa si esta en el iniio
    if(inicioV == 0){
        avance == 0;
       inicio();

       //inicioV = 1;
       }
        else{
    figuraActual(figura);
	fijos();}
    borders();
        cuadricula();

    glutSwapBuffers();
	//glMatrixMode(GL_MODELVIEW);
}
void myTimer( int valor)
{
	updateAnteriores();
    movY = movY - avance;
    glutPostRedisplay();
    glutTimerFunc(rapidez, myTimer,1);
}

void reshape(int w, int h)
{
      glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-20, 580, -20, 580, -290, 290);//izq, der, abajo, arriba, cerca
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);//ajuste el tamaño de la ventana
    //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
     glLoadIdentity ();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
    case 'P':
    case 'p':
        if(avance == 0){
            avance = 20;
            pausaV = 0;
        }
        else{
            avance = 0;
            pausaV = 1;
        }
		break;
case 'I':
    case 'i':
        inicioV = 1;
        avance = 20;
		break;

    case 'E':
    case 'e':
        exit(-1);
	case ' ':
		rapidez=1;
		break;
    default:
        break;
    }
}
void special(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
				tocaPiso=0;
				updateAnteriores();
                movX=movX-avance;
                glutPostRedisplay();
                break;
        case GLUT_KEY_RIGHT:
				tocaPiso=0;
				updateAnteriores();
                movX=movX+avance;
				glutPostRedisplay();
				break;
        case GLUT_KEY_DOWN:
			updateAnteriores();
            movY=movY-avance;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
			tocaPiso=0;
			updateAnteriores();
            rotacion-=90;
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
    //init();
    initRendering();
    //createList();
    glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(special);
    glutReshapeFunc(reshape);
	glutTimerFunc(500,myTimer,1);
	addMenues();
    glutMainLoop();
    return 0;
}

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}
Image::~Image()
{
    delete[] pixels;
}
namespace
{
//Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

//Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

//Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

//Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

//Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}
Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
    case 40:
        //V3
        width = readInt(input);
        height = readInt(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = readShort(input);
        height = readShort(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}
