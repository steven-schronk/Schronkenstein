CC=gcc

CFLAGS_REL=-Wall -ansi -O0 -lglut -lm
#CFLAGS_DBG=-Wall -Werror -pedantic -std=c99 -ansi -DDEBUG -g -O0 -ggdb3 -Wextra -Wno-missing-field-initializers -llibxml2
CFLAGS_DBG=-Wall -pedantic -std=c99 -ansi -DDEBUG -g -O0 -ggdb3 -Wextra -Wno-missing-field-initializers -lglut -lm
CFLAGS_SML=-Wall -ansi -Os -lglut -lm
CFLAGS_FAS=-Wall -ansi -O3 -lglut -lm

OBJS=main.c
OUT=-o main

fast: $(OBJS)
	$(CC) $(CFLAGS_FAS) $(OUT) $^

small: $(OBJS)
	$(CC) $(CFLAGS_SML) $(OUT) $^

debug: $(OBJS)
	$(CC) $(CFLAGS_DBG) $(OUT) $^

clean:
	rm -f main *.o
