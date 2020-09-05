all:
	gcc main.c -std=c89 -Ofast -Wall -Wextra -pedantic -o yamatrix

clean:
	rm -f yamatrix

install: all
	cp -f yamatrix /usr/local/bin/yamatrix

uninstall:
	rm -f /usr/local/bin/yamatrix
