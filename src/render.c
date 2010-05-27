#include <stdbool.h>

#include <GL/glut.h>

#define WALL_HEIGHT 7

void draw_wall(short xStart, short xStop, short yStart, short yStop)
{
	glBegin(GL_QUADS);
		glVertex3i(xStart, yStart, 0);		/* tl - x,y,z */
		glVertex3i(xStart, yStart, WALL_HEIGHT);	/* tr */
		glVertex3i(xStop, yStop,  WALL_HEIGHT);	/* br */
		glVertex3i(xStop, yStop, 0);		/* bl */
	glEnd();
}

/* draws coordinates from origin - useful for debugging */
void draw_coords(void)
{
	/* x-axis - blue ----------------------------*/
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES); /* vertical line */
		glVertex3i(0,0,0);
		glVertex3i(1,0,0);
	glEnd();

	glBegin(GL_LINES); /* arrow head */
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.875f, 0.125f, 0.0f);
	glEnd();

	glBegin(GL_LINES); /* arrow head */
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.875f, -0.125f, 0.0f);
	glEnd();

	glBegin(GL_LINES); /* character "X" */
		glVertex3f(1.25, -.125, 0.0);
		glVertex3f(1.5, .125, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(1.5, -.125, 0.0);
		glVertex3f(1.25, .125, 0.0);
	glEnd();

	/* y-axis - green ----------------------------*/
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES); /* vertical line */
		glVertex3i(0,0,0);
		glVertex3i(0,1,0);
	glEnd();

	glBegin(GL_LINES); /* arrow head */
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.125f, 0.875f, 0.0f);
	glEnd();

	glBegin(GL_LINES); /* arrow head */
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.125f, 0.875f, 0.0f);
	glEnd();

	glBegin(GL_LINES); /* character "Y" */
		glVertex3f( 0.0, 1.375,0.0);
		glVertex3f(.125, 1.5, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-.125, 1.5, 0.0);
		glVertex3f(0.0, 1.375, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.0,1.375, 0.0);
		glVertex3f(0.0,1.25, 0.0);
	glEnd();

	/* z-axis - red ----------------------------*/
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES); /* vertical line */
		glVertex3i(0,0,0);
		glVertex3i(0,0,1);
	glEnd();

	glBegin(GL_LINES); /* arrow head */
		glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.125f, 0.0f, 0.875f);
	glEnd();

	glBegin(GL_LINES); /* arrow head */
		glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.125f, 0.0f, 0.875f);
	glEnd();

	glBegin(GL_LINES); /* character "Z" */
		glVertex3f(-.125, 0.0, 1.25);
		glVertex3f(.125, 0.0, 1.25);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(.125, 0.0, 1.25);
		glVertex3f(-.125, 0.0, 1.50);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-.125, 0.0, 1.50);
		glVertex3f(.125, 0.0, 1.50);
	glEnd();

	/* draw center point */
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

/* toggle engine from shaded to wireframe */
void draw_wireframe(void)
{
	int polygonMode[2];

	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	if(polygonMode[1] == GL_FILL)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
}
