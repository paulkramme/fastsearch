all:
	clang -Weverything main.c -o fast-search
clean:
	rm fast-search fs.conf
