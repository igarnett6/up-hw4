shell: shell.c
	gcc -Wall -std=c99 -o shell shell.c

clean:
	rm -f shell
