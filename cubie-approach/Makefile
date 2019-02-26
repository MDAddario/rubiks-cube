SRCS = rubiks.c minimax.c
OBJS = ${SRCS:.c=.o}
HDS = ${SRCS:.c=.h}

all: main

main: main.c ${OBJS}
	gcc main.c ${OBJS} -o main

.c.o: ${SRCS} ${HDS}
	gcc -c $<

clean:
	rm -f main ${OBJS} output_cube.bmp