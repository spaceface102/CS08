build/array.o: srcs/array.c hdrs/array.h
	gcc srcs/array.c -ansi -std=c99 -Wall -Wpedantic -g -I hdrs  -c -o  build/array.o

hdrs/array.h:
