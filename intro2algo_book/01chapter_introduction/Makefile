#FIELDS OFTEN MODIFIED
EXEC = a.out
DEPSDIR = deps
OBJSDIR = build
HDRSDIR = hdrs #rember to include -I to specify where the header files are
CC = gcc
CFLAGS = -Wall -Wpedantic -g -I $(HDRSDIR)
LFLAGS = -Wall -Wpedantic -g
#DONT USE ".", use $(shell pwd) to get an 
#absolute path to current directory
#else, just the name of the directory in
#the current directory, such as srcs
SRCSDIR = srcs


#FIELDS RARELY MODIFIED
SRCS = $(patsubst $(SRCSDIR)/%.c, %.c, $(wildcard $(SRCSDIR)/*.c))
OBJS = $(patsubst %.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS = $(patsubst %.c, $(DEPSDIR)/%.d, $(SRCS))


#DEPS BUILDING SPECIFIC FIELDS (RARELY MODIFIED)
TARGET = $(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $<)
DEPFLAGS = -MM -MP -MF $@ -MT $(TARGET) -I $(HDRSDIR)
PY_DEPARGS = $@ "$(CC) $< $(CFLAGS) -c -o $(TARGET)"


.PHONY: clean all

all: $(EXEC)

#this does the linking
$(EXEC): $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(DEPSDIR)/%.d: $(SRCSDIR)/%.c
	@mkdir -p $(DEPSDIR)
	@mkdir -p $(OBJSDIR)
	#making $@
	@$(CC) $(DEPFLAGS) $<
	@./make_depfiles.py $(PY_DEPARGS)

clean:
	rm -f $(OBJSDIR)/*.o
	rm -f $(DEPSDIR)/*.d
	rm -f $(EXEC)

include $(DEPS)

#WHAT I LEARNED MAKING THIS MAKEFILE
#@ infront of a line a recipie, shuts up the output to the terminal
#mkdir -p ensures that no errors are thrown even if the file already exists
#.PHONY targets are used when the target is not a file
#-MM shows all the, non standard, dependencies that a c file has (gcc)
#	One thing to watch out for is that the rule will only keep the path
#	of the source file in the depenency/prerequiste list IF it is not "."
#	(not sure of ".."), but in those cases, it is just better to use an
#	absolute address. This is not a problem if for example its like srcs/main.c
#-MP adds a phony target for all the header files created by the -MM rule (gcc)
#-MF allows you to change the name of the output "sub makefile" made by the -MM option
#-MT allows you to change the target of the rule made by -MM (useful for organizing)
#I had some more experience with python3 -c and python3 - <<-EOF which are both useful
# 	for "one line" comand line python
#the include directive/keyword in make more or less works by opening an exisiting
#	makefile and reading it as if it where in this makefile. The extra cool thing
#	is, if the planned included makefile does not exists, assuming you have a
#	a rule to build that make file, make will go ahead and make the "sub makefile"
#	and then actually include it! Pretty darn cool
#	Also, I think that no matter what, this is also the first thing to be run
#	in the makefile. I mean just run make clean twice consecutively, and I think
#	you can start to piece it together
#rules with just <filename>.o:<filename>.c will run without any recipie
#	and will compile using what I would like to assume, core variables
#	such as $(CC) which choses compiler, and $(CFLAGS) which chooses aditional
#	flags for the compiling
#More on the previous, I also learned that this is finiky and changing the target
#	a little bit to forexample build/<filename>.o will cause it to NOT automatically
#	compile. That is why I ended making a custom python3 script to explicity insert
#	the compiling step