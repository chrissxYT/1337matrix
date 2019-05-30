all:
	@gcc main.c -Ofast -o matrix

test:
	@gcc main.c -Og -o matrix
	@./matrix

clean:
	@rm -f matrix
