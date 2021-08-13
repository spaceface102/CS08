build/main.o: srcs/main.c hdrs/mysort.h hdrs/insertion_sort.h \
 hdrs/sorttest.h hdrs/array.h
	gcc srcs/main.c -ansi -std=c99 -Wall -Wpedantic -g -I hdrs  -c -o  build/main.o

hdrs/mysort.h:

hdrs/insertion_sort.h:

hdrs/sorttest.h:

hdrs/array.h:
