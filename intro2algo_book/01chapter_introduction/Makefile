CC = gcc #I added this to change default compiler
CPPFLAGS += -MMD -MP #these flags ensure auto dependencies based on c file
SRC = $(wildcard *.c) #getting a list of all the local .c files
EXEC = a.out

$(EXEC): $(SRC:%.c=%.o)
	$(CC) -o $@ $^

clean:
	rm -f *.o
	rm -f *.d
	rm -f $(EXEC)

-include $(SRC:%.c=%.d)

#I honestly don't have a real idea
#of how this shit is working, but gah
#damn its fucking working
#my current idea is that the make file
#has a defualt compiling recipe when
#no recipe is defined. therefore
#by doing -include an all the created
#rules from the CPPFLAGS, it defualts
#to whatever is specified by what I would
#like to assume are special variables (CC as
#an example)