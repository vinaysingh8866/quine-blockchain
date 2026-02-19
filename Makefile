#!/usr/bin/env make

CC = cc
CFLAGS = -std=gnu17 -O2 -Wall -Wextra -pedantic
PROG = prog

all: ${PROG}

${PROG}: ${PROG}.c
	${CC} ${CFLAGS} -o $@ $<

try: ${PROG}
	@./try.sh

clean:
	rm -f ${PROG}
	rm -f gen[0-9]* corrupt

clobber: clean
	rm -f ${PROG}

.PHONY: all try clean clobber
