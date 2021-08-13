#FIELDS OFTEN MODIFIED
EXEC = a.out
DEPSDIR = deps
OBJSDIR = build
CC = gcc
#DONT USE ".", use $(shell pwd) to get an 
#absolute path to current directory
#else, just the name of the directory in
#the current directory, such as srcs
SRCSDIR = srcs


#FIELDS RARELY MODIFIED
SRCS = $(patsubst $(SRCSDIR)/%.c, %.c, $(wildcard $(SRCSDIR)/*.c)) #getting a list of all the local .c files
OBJS = $(patsubst %.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS = $(patsubst %.c, $(DEPSDIR)/%.d, $(SRCS))


.PHONY: clean

#this does the linking
$(EXEC): $(OBJS)
	$(CC) $^ -o $@

#cretes a dependency file
#-MM creates a core rule
#-MP creates a phony rules (help avoid problems with deleted headers)
#-MF sets the name of the dependency file to a custom name
#-MT sets a different target name for the generated rule
#final $< states the src file to extract the rules from
$(DEPSDIR)/%.d: $(SRCSDIR)/%.c
	@mkdir -p $(DEPSDIR)
	@mkdir -p $(OBJSDIR)
	#making $@, remove leading @ in the Makefile for debuging
	@$(CC) -MM -MP -MF $@ -MT $(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $<) $<
	@./make_depfiles.py $@ "$(CC) $< -c -o $(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $<)"

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
#rules with just <filename>.o:<filename>.c will run without any recipie
#	and will compile using what I would like to assume, core variables
#	such as $(CC) which choses compiler, and $(CFLAGS) which chooses aditional
#	flags for the compiling
#More on the previous, I also learned that this is finiky and changing the target
#	a little bit to forexample build/<filename>.o will cause it to NOT automatically
#	compile. That is why I ended making a custom python3 script to explicity insert
#	the compiling step