all:
	clang -Weverything main.c -o fast-search -ansi
clean:
	rm fast-search
