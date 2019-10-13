all:
	gcc main.c -Ofast -o yamatrix

clean:
	rm -f yamatrix

install:
	cp -f yamatrix /usr/bin/yamatrix

uninstall:
	rm -f /usr/bin/yamatrix
