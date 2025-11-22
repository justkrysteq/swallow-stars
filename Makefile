COMPILER = gcc
CFLAGS = -c
LDFLAGS = -lncurses

SRCS = main.c $(wildcard modules/*.c)
OBJS = $(SRCS:.c=.o)

all: swallow-stars

swallow-stars: ${OBJS}
	${COMPILER} -o $@ $^ ${LDFLAGS}
	rm -f ${OBJS}

main.o: main.c
	${COMPILER} ${CFLAGS} main.c

modules/%.o: modules/%.c
	${COMPILER} ${CFLAGS} $< -o $@

clean:
	rm -f $(OBJS) swallow-stars
