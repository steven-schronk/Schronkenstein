#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WALL_HEIGHT 7

GLuint texture[1];

void draw_wall(short xStart, short xStop, short yStart, short yStop)
{
	glEnable (GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3i(xStart, yStart, 0);		/* tl - x,y,z */
		glTexCoord2f(0.0, 1.0);
		glVertex3i(xStart, yStart, WALL_HEIGHT);	/* tr */
		glTexCoord2f(1.0, 1.0);
		glVertex3i(xStop, yStop,  WALL_HEIGHT);	/* br */
		glTexCoord2f(1.0, 0.0);
		glVertex3i(xStop, yStop, 0);		/* bl */
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void draw_floor(short xStart, short xStop, short yStart, short yStop)
{
	glEnable (GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glVertex2i(xStart, yStart);
		glVertex2i(xStart,  yStop);
		glVertex2i(xStop, yStop);
		glVertex2i(xStop, yStart);
		glVertex2i(xStart, yStart);
	glEnd();
	glDisable(GL_TEXTURE_2D);
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

/*
  Loads textures from TGA files

  files must be in TGA format

  gimp - add alpha channel and put in RGB mode before saving
  check the status with the "file" command in Linux.
*/
bool LoadTGA(TextureImage * texture, char *filename)
{
	GLubyte TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLubyte TGAcompare[12];
	GLubyte header[6];
	GLuint bytesPerPixel;
	GLuint imageSize;
	GLuint temp;
	GLuint type = GL_RGBA;
	GLuint i = 0;
	FILE * file = fopen (filename, "rb");

	if (file == NULL) {  exit_error(4, "Could Not Open Texture File"); }
	if(fread (TGAcompare, 1, sizeof (TGAcompare), file) != sizeof (TGAcompare)) { exit_error(5, "Header of Texture File Does Not Contain 12 Bytes"); }
	if(memcmp (TGAheader, TGAcompare, sizeof (TGAheader)) != 0) {  exit_error(6, "Header File Of Texture Is Not Correct"); }
	if(fread (header, 1, sizeof(header), file) != sizeof (header)) { exit_error(7, "Could Not Read Header Bytes of Texture File"); }

	texture->width = header[1] * 256 + header[0];
	texture->height = header[3] * 256 + header[2];
	if (texture->width <= 0 ||
		texture->height <= 0 ||
		(header[4] != 24 && header[4] != 32))
	{
		fclose (file);
		return false;
	}

	texture->bpp = header[4];
	bytesPerPixel = texture->bpp / 8;
	imageSize = texture->width * texture->height * bytesPerPixel;
	texture->imageData = (GLubyte *) malloc (imageSize);
	if (texture->imageData == NULL ||
		fread (texture->imageData, 1, imageSize, file) != imageSize)
	{
		if (texture->imageData != NULL)
		free (texture->imageData);
		fclose (file);
	return false;
	}
	for (i = 0; i < (int)(imageSize); i += bytesPerPixel)
	{
		temp = texture->imageData[i];	
		texture->imageData[i] = texture->imageData[i + 2];
		texture->imageData[i + 2] = temp;
	}
	fclose (file);

	glGenTextures (1, &texture[0].texID);
	glBindTexture (GL_TEXTURE_2D, texture[0].texID);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (texture[0].bpp == 24)
	{
		type = GL_RGB;
	}
	glTexImage2D (GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height,
		  0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
	return true;
}
