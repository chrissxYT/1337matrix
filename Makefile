all:
	gcc main.c -Ofast -o yamatrix

clean:
	rm -f yamatrix

install:
	cp -f yamatrix /usr/local/bin/yamatrix

uninstall:
	rm -f /usr/local/bin/yamatrix
