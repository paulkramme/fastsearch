all:
	clang -Weverything main.c -o fastsearch -ansi
clean:
	rm fastsearch
