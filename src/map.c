#include <stdio.h>
#include <string.h>

#include "error.c"
#include "main.h"
#include "types.h"

/* open items file and gather map data */
int map_items_init()
{
	return 0;
}

/* remove extra chars from map file - makes parsing easier */
void line_clean(char *line)
{
	char *p1 = line;
	char *p2 = line;

	/* remove all whitespace from each line */
	while(*p1 != '\0')
	{
		if(isspace(*p1)) { ++p1; }
		else { *p2++ = *p1++; }
	}
	*p2 = '\0';

	/* reset pointer and remove comments */
	p1 = line; p2 = line;
	while(*p1 != '\0')
	{
		if(*p1 == '#')
		{
			*p1 = '\0';
			break;
		}
		p1++;
	}
}

/* open walls file and gather map data */
void map_init(char *mapname, struct Wall *walls, struct Map *map)
{
	FILE *pMapfile;
	int wall_count = 0;
	char line[80];
	char *token;
	int tokcount = 0;
	char texture[80];

	map->TextureCount = 0;
	map->WallCount = 0;

	if((pMapfile = fopen(mapname, "r")) == NULL)
		exit_error(1, "Cannot Open Map File");

	/* divide file into lines while removing whitespaces and removing comments */
	while(fgets(line, sizeof line, pMapfile )!= NULL)
	{
		line_clean(line);
		printf("%s\n", line);

		/* place each line into correct data structure */
		switch(line[0])
		{
			case 'w':
				printf("Found Wall\n");
				tokcount = 1;
				token = strtok(line, "=,:");
				while (token != NULL)
				{
					token = strtok(NULL, "=,:");
					printf("TOKEN: %s\n", token);
					if(token != NULL)
					{
						if(tokcount == 1) { walls[wall_count].xStart = atoi(token); }
						if(tokcount == 2) { walls[wall_count].yStart = atoi(token); }
						if(tokcount == 3) { walls[wall_count].xStop  = atoi(token); }
						if(tokcount == 4) { walls[wall_count].yStop  = atoi(token); }
					}
					tokcount++;
				}
				walls[wall_count].texture = malloc((strlen(texture)+1) * sizeof( char *));  /* get memory for tex name */
				if(walls[wall_count].texture == NULL) { exit_error(0, "Could not allocate enough memory"); }
				/* copy texture name to this struct */
				strcpy(walls[wall_count].texture, texture);
				map->WallCount++;
				wall_count++;
				break;
			case 't':
				printf("Found Texture\n");
				token = strtok(line, "="); /* not a typeo :( */
				token = strtok(NULL, "=");

				/* store texture in temp var */
				strcpy(texture, token);

				/* post texture in map struct */
				walls[wall_count].texture = malloc((strlen(token)+1) * sizeof( char *)); /* get memory for tex name */
				if(walls[wall_count].texture == NULL) { exit_error(0, "Could not allocate enough memory"); }
				strcpy(walls[wall_count].texture, texture);
				map->TextureCount++;
				break;
			case 's':
				printf("Found Start Point\n");
				tokcount = 1;
				token = strtok(line, "=,:");
				while (token != NULL)
				{
					token = strtok(NULL, "=,:");
					printf("TOKEN: %s\n", token);
					if(token != NULL)
					{
						if(tokcount == 1) { map->startX = atoi(token); }
						if(tokcount == 2) { map->startY = atoi(token); }
					}
					tokcount++;
				}
			default:
				break;
		}
	}
	fclose(pMapfile);
}
