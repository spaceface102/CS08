build/array.o: srcs/array.c hdrs/array.h
	gcc srcs/array.c -Wall -Wpedantic -g -I hdrs  -c -o  build/array.o

hdrs/array.h:
