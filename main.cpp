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
int movX, movY, movXant, movYant;
int avance = 20;
int tocaPiso;
int figura, rotacion = 0, rotacionant=0;
static GLuint texName[36];
const int TEXTURE_COUNT=6;


void updateAnteriores(){
	rotacionant=rotacion;
	movXant=movX;
	movYant=movY;
}
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
		tocaPiso++;
		movY=movYant;
		movX=movXant;
		rotacion=rotacionant;
		return true;
	}
	return false;
}
void fijar(int x, int y){
	int fila=((y-10)/20)+1;
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
		movY-=20;
	}
}
void nuevaPieza(){
	tocaPiso=0;
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
            figura = 3;
            break;
        case 5://ese
            figura = 3;
            break;
        case 6://zeta
            figura = 3;
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
{GLuint i=0;
       GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat directedLight[] = {0.9f, 0.9f, 0.9f, 1.0f};
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


    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen1.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen2.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen3.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen4.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen5.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen6.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen7.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen8.bmp");loadTexture(image,i++);
    image = loadBMP("/Users/Raul/Desktop/7mo/Graficas/3er Parcial/Proyectos/Texturas/img/imagen9.bmp");loadTexture(image,i++);
    delete image;
}
//funcion que despliega los bordes
void borders(){
     //cuadro exterior
    glColor3f(0.5, 0.5, 0.8);
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
	glEnd();
}
//para que marque la separación entre lo cubos
void cuadricula(){
    //lineas verticuales
    glColor3f(0, 0, 0);
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

             glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
            glEnable(GL_TEXTURE_GEN_T);
            glBindTexture(GL_TEXTURE_2D, texName[3]);
            glutSolidCube(20);
            glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
            glDisable(GL_TEXTURE_GEN_T);
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
 void fijos(){
	 for(int i=1; i<29; i++){
		 for(int z=0; z<18; z++){
			 switch(matriz[i][z]){
				case 0:
				 break;
				default:
					glPushMatrix();
						glColor3f(0, 1, 0);
						glTranslatef((z*20)+10,((i-1)*20)+10,0);
						glutSolidCube(20);
					glPopMatrix();
					break;
			 }
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    borders();
    //figuraActual(figura);
	ele();
	fijos();
    cuadricula();
    glutSwapBuffers();
	//glMatrixMode(GL_MODELVIEW);
}
void myTimer( int valor)
{
	updateAnteriores();
    movY = movY - avance;
    glutPostRedisplay();
    glutTimerFunc(500, myTimer,1);
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
        }
        else{
            avance = 0;
        }
		break;

    case 'E':
    case 'e':
        exit(-1);
    default:
        break;
    }
}
void special(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
				updateAnteriores();
                movX=movX-avance;
                glutPostRedisplay();
                break;
        case GLUT_KEY_RIGHT:
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
    init();
    //createList();
    glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(special);
    glutReshapeFunc(reshape);
	glutTimerFunc(500,myTimer,1);
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
