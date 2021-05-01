CC ?= cc
CFLAGS ?= -Ofast -Wall -Wextra -pedantic

all:
	$(CC) main.c $(CFLAGS) -o yamatrix

clean:
	rm -f yamatrix

install: all
	cp -f yamatrix /usr/local/bin/yamatrix

uninstall:
	rm -f /usr/local/bin/yamatrix
