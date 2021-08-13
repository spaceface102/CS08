build/insertion_sort.o: srcs/insertion_sort.c hdrs/insertion_sort.h
	gcc srcs/insertion_sort.c -ansi -std=c99 -Wall -Wpedantic -g -I hdrs  -c -o  build/insertion_sort.o

hdrs/insertion_sort.h:
