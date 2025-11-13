CFLAGS = -lncurses

swallow-stars: main.o
	gcc ${CFLAGS} -o swallow-stars main.o

main.o: main.c
	gcc ${CFLAGS} -c main.c

clean:
	rm *.o swallow-stars
