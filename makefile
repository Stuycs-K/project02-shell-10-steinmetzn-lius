.PHONY: compile run clean
compile shell: main.o shell.o
	@gcc -o shell main.o shell.o
main.o: main.c shell.h
	@gcc -c main.c
shell.o: shell.c shell.h
	@gcc -c shell.c
run: shell
	@./shell
clean:
	rm *.o
	rm shell
