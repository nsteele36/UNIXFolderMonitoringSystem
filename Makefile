#PROGRAM5 -MAKEFILE
#PROGRAMMED BY: NICHOLAS STEELE (nss150130) 
#Template from : Dr. Perkins
#CS3377.501

# Set up info for C++ implicit rule
CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -I ./include -I /home/011/n/ns/nss150130/include 

#
# Set up any Linker Flags
LDFLAGS =  -static -L/home/011/n/ns/nss150130/lib
LDLIBS =-lrudeconfig
#
# We choose the project name.  This is used in building the file name for the backup target
PROJECTNAME = program5
#
# We choose the source files to include and name the output
SRCS = inotifyFunctions.cc loggingFunctions.cc parsecmdline.cc parseconfigfile.cc processControl.cc program5.cc signalHandling.cc

#
# We choose the name of the executable to be created
EXEC = cs3377dirmond

#
# You normally don't need to change anything below here.
# ======================================================
#
OBJS = $(SRCS:cc=o)

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ \#* 

Makefile: $(SRCS:.cc=.d)

# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# Include the dependency files
-include $(SRCS:.cc=.d)

