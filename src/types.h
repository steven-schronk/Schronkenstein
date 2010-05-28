#ifndef CUSTOM_TYPES
#define CUSTOM_TYPES

#define MAX_WALLS 100	/* this is the maximum number of walls for engine */
#define MAX_FLOORS 100	/* this is the maximum number of floors for engine */
#define PI 3.141592654f

typedef struct Wall
{
	short xStart;
	short xStop;
	short yStart;
	short yStop;
	char *texture;
} wall;

typedef struct Map
{
	short WallCount;
	short FloorCount;
	short TextureCount;
	short startX;
	short startY;
} maps;

typedef struct Input
{
	int mouseLf;
	int mouseRt;
	int mouseX;
	int mouseY;
} inputs;

typedef struct
{
	GLubyte	*imageData;	/*  Image Data (Up To 32 Bits) */
	GLuint	bpp;		/* Image Color Depth In Bits Per Pixel. */
	GLuint	width;		/* Image Width */
	GLuint	height;		/* Image Height */
	GLuint	texID;		/* Texture ID Used To Select A Texture */
} TextureImage;

#endif
