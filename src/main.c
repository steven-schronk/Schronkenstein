#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glut.h>

#include "map.c"
#include "render.c"
#include "types.h"

struct Wall walls[MAX_WALLS];
struct Wall floors[MAX_FLOORS];
struct Map map;
struct Input input;

/* TODO: REMOVE THESE AND MAKE A STRUCT OF THE DATA */
float xpos = 0, ypos = 0, xrot = 0, zrot = 0, angle = 0.0; /* removed: y-pos = 0 */
float lastx, lasty;

/* positions of the cubes */
float positiony[10];
float positionx[10];

/* TODO: Delete later */
void cubepositions(void) /* set the positions of the cubes */
{
	int i = 0;
	for (;i<10;i++)
	{
		positiony[i] = rand()%5 + 1;
		positionx[i] = rand()%5 + 1;
	}
}

/* TODO: Delete later */
void cube(void)
{
	int i = 0;
	for (;i<10 - 1;i++)
	{
		glPushMatrix();
		glTranslated(-positionx[i + 1] * 10, -positiony[i + 1] * 10, 0.00f); /*translate the cube*/
		glutSolidCube(2); /* draw the cube */
		glPopMatrix();
	}
}

/* draw string of text data on screen */
void DrawString(int x, int y, char *string)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void display(void)
{
	int width, height, i;

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* find width and height of window */
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	glLoadIdentity();


	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);


	/* rotate and position camera */
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);  /* rotate our camera on the y-axis (up and down)*/
	glTranslated(xpos, -ypos, -4.0f);

	draw_coords();

	/* draw floors */
	for( i = 0; i < map.FloorCount; i++)
	{
		draw_floor(floors[i].xStart, floors[i].xStop, floors[i].yStart, floors[i].yStop);
	}

	/* draw walls */
	for( i = 0; i < map.WallCount; i++)
	{
		draw_wall(walls[i].xStart, walls[i].xStop, walls[i].yStart, walls[i].yStop);
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	glFlush();
	glutSwapBuffers();
}

void init(void)
{
	TextureImage tex;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_COLOR_MATERIAL);
	glEnable (GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glShadeModel (GL_SMOOTH);

	LoadTGA(&tex, "../textures/BookshelfL.tga");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &tex.texID);
	glBindTexture(GL_TEXTURE_2D, tex.texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.imageData);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int x, int y)
{
	input.mouseX = x; /* makes compiler happy */
	input.mouseY = y; /* makes compiler happy */
}

void mouseMovement(int x, int y)
{
	int diffx = x-lastx;		/* check the difference between the current x and the last x position */
	int diffy = y-lasty;		/* check the difference between the current y and the last y position */

	lastx = x;			/* set lastx to the current x position */
	lasty = y;			/* set lasty to the current y position */
	xrot += (float)diffy;		/* set the xrot to xrot with the addition of the difference in the y position */
	zrot += (float)diffx;		/* set the xrot to zrot with the addition of the difference in the x position */
	display();
}

void keyboard(unsigned char key, int x, int y)
{
	float xrotrad, zrotrad;

	x = 0;
	y = 0;

	if(key == 's') /* move reverse */
	{
		zrotrad = (zrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos += (float)(sin(zrotrad)) ;
		ypos -= (float)(cos(zrotrad)) ;
		/*y-pos -= (float)(sin(xrotrad)) ;*/
	}

	if(key == 'w') /* move forward */
	{
		zrotrad = (zrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos -= (float)(sin(zrotrad));
		ypos += (float)(cos(zrotrad)) ;
		/*y-pos += (float)(sin(xrotrad));*/
	}

	if(key == 'a') /* strafe left */
	{
		zrotrad = (zrot / 180 * PI);
		xpos -= (float)(cos(zrotrad)) * 0.1;
		ypos -= (float)(sin(zrotrad)) * 0.1;
	}

	if(key == 'd') /* strafe right */
	{
		zrotrad = (zrot / 180 * PI);
		xpos += (float)(cos(zrotrad)) * 0.1;
		ypos += (float)(sin(zrotrad)) * 0.1;
	}

	if(key == 'f') /* toggle wireframe */
	{
		draw_wireframe();
	}

	if (key == 27)
	{
		exit(0);
	}
	/* printf("xpos:%f\ty-pos:%f\typos:%f\txrot:%f\tzrot:%f\tangle:%f\t\n", xpos, y-pos, ypos, xrot, zrot, angle); */
	display();
}

int main(int argc, char **argv)
{
	map_init("../maps/1.map", walls, floors, &map);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
 	glutInitWindowSize(600,500);
	glutInitWindowPosition(100,100);

	glutCreateWindow("Schronkenstein");

	/* glutFullScreen(); */

	init();
	/*cubepositions();*/

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();
	return 0;
}
