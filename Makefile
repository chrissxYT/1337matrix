all:
	@gcc main.c -Ofast -o matrix

test:
	@gcc main.c -Og -o matrix
	@./matrix

clean:
	@rm -f matrix

install:
	@cp -f matrix /usr/bin/matrix

uninstall:
	@rm -f /usr/bin/matrix
