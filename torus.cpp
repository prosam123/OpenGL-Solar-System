#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;
#define PI 3.14159265

static int isAnimate = 0;
static int animationPeriod = 100;
static float latAngle = 0.0, longAngle = 0.0, Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;

void draw_mercury(){
	glRotatef(longAngle , 0.0 , 0.0 , 1.0);
	glTranslatef(7.0 , 0.0 , 0.0);
	glColor3f(0.5 , 0.075 , 0.0);
	glutWireSphere(1.75, 100.0, 100.0);	

	// glRotatef(latAngle , 0.0 , 0.0 , 1.0);
	// glTranslatef(-12.0 , 0.0 , 0.0);
	// glTranslatef(16.0 , 0.0 , 0.0);
	// glColor3f(1.0 , 1.0 , 1.0);
	// glutWireSphere(1.0, 100.0, 100.0);
}

void draw_venus(){
	// glRotatef(longAngle , 0.0 , 0.0 , 1.0);
	glTranslatef(9.0 , 0.0 , 0.0);
	glColor3f(1.0 , 0.0 , 0.0);
	glutWireSphere(2.0, 100.0, 100.0);
}
void draw_earth(){
	// glRotatef(longAngle , 0.0 , 0.0 , 1.0);
	glTranslatef(9.0 , 0.0 , 0.0);
	glColor3f(0.0 , 0.0 , 1.0);
	glutWireSphere(2.0, 100.0, 100.0);
}

void drawScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0 , 0.0 , -25.0);
	
	glRotatef(Xangle , 1.0 , 0.0 , 0.0);
	glRotatef(Yangle , 0.0 , 1.0 , 0.0);
	glRotatef(Zangle , 0.0 , 0.0 , 1.0);	

	glColor3f(1.0 , 1.0 , 0.0);
	glutWireSphere(2.0, 100.0, 100.0);

	glColor3f(0.0 , 1.0 , 0.0);	
	// glutWireTorus(0.01, 7.0, 40.0, 40.0);//mercury ring
	// glutWireTorus(0.01, 16.0, 40.0, 40.0);//venus ring

	draw_mercury();
	draw_venus();
	draw_earth();


	glutSwapBuffers();
}

void setup(void){
	glClearColor(.0 , .0 , .0 , 0.0);
	glEnable(GL_DEPTH_TEST);
}

void resize(int w,int h){
	glViewport(0 , 0 , w , h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0 , 5.0 , -5.0 , 5.0 , 5.0 , 100.0);
	glMatrixMode(GL_MODELVIEW);
}


void animate(int value){
	if(isAnimate){
		latAngle += 5.0;
		if(latAngle > 360.0)latAngle -= 360.0;
		longAngle += 1.0;
		if(longAngle > 360.0)longAngle -= 360.0;
		
		glutPostRedisplay();
		glutTimerFunc(animationPeriod,animate,1);
	}
}

void keyInput(unsigned char key,int x,int y){
	switch(key){
		case 27:
			exit(0);
			break;
		case ' ':
			if(isAnimate)isAnimate=0;
			else{
				isAnimate=1;
				animate(1);
			}
			break;
		case 'q':
			Xangle += 5.0;
			if(Xangle > 360.0)Xangle -= 360.0;
			glutPostRedisplay();
			break;
		case 'w':
			Xangle -= 5.0;
			if(Xangle < 0.0)Xangle += 360.0;
			glutPostRedisplay();
			break;
		case 'a':
			Yangle += 5.0;
			if(Yangle > 360.0)Yangle -= 360.0;
			glutPostRedisplay();
			break;
		case 's':
			Yangle -= 5.0;
			if(Yangle < 0.0)Yangle += 360.0;
			glutPostRedisplay();
			break;
		case 'z':
			Zangle += 5.0;
			if(Zangle > 360.0)Zangle -= 360.0;
			glutPostRedisplay();
			break;
		case 'x':
			Zangle -= 5.0;
			if(Zangle < 0.0)Zangle += 360.0;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}


void specialKeyInput(int key,int x,int y){
	if(key==GLUT_KEY_DOWN)animationPeriod+=5;
	if(key==GLUT_KEY_UP && animationPeriod>5)animationPeriod-=5;
	glutPostRedisplay();
}

void printInteraction(void){
	cout<<"Solar System\n";
}

int main(int argc,char** argv){
	printInteraction();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Solar System");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	setup();
	glutMainLoop();
}
