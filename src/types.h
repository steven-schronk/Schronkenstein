#ifndef CUSTOM_TYPES
#define CUSTOM_TYPES

#define MAX_WALLS 100 /* this is the maximum number of walls for engine */
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

#endif
