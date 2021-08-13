build/sorttest.o: srcs/sorttest.c hdrs/sorttest.h hdrs/array.h
	gcc srcs/sorttest.c -Wall -Wpedantic -g -I hdrs  -c -o  build/sorttest.o

hdrs/sorttest.h:

hdrs/array.h:
