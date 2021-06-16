GCC=gcc -g
CFLAGS=-c -Wall -Werror
SFLAG=-fpic
INCLUDE=lib/
BINDIR=build/
OBJDIR=build/
LIBDIR=build/
SRCDIR=lib/
APPDIR=app/
APPOBJ=app/
SRCEXT=c
OBJEXT=o
SYSREPO_LFLAG=-lsysrepo
YANG_LFLAG=-lyang
DL_LFLAG=-ldl
SOURCES_LIB=$(wildcard $(SRCDIR)*.c)
OBJECTS_LIB := $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SOURCES_LIB:.$(SRCEXT)=.$(OBJEXT)))
SOURCES_APP=$(wildcard $(APPDIR)*.c)
OBJECTS_APP := $(patsubst $(APPDIR)%,$(APPOBJ)%,$(SOURCES_APP:.$(SRCEXT)=.$(OBJEXT)))
# $@, The name of target
# $^, The name of all depencency 
# $<, The name of first depencency
# $?, The name of all depencencies newer than the target space seperated file
# $+, The name of all dependencies seperated by space with dupicated names included and in the same order as in the rules.

all: $(BINDIR)libruapp.so $(BINDIR)ruapp
$(BINDIR)libruapp.so: $(OBJECTS_LIB)
	@echo "\nCreating dynamic library"
	$(GCC) $^ -shared -o $@
	@echo "Done, created $@"    

$(OBJDIR)%.o: $(SRCDIR)%.c
	@echo "\nCompiling $<"
	$(GCC) $(CFLAGS) $(SFLAG) -I$(INCLUDE)  $<  -o $@
	@echo "Done"

$(APPOBJ)%.o: $(APPDIR)%.c
	@echo "\nCompiling $<"
	$(GCC) $(CFLAGS) -I./$(APPOBJ)  $<  -o $@
	@echo "Done"

$(BINDIR)ruapp: $(OBJECTS_APP)
	@echo "\nCreating ruapp"
	$(GCC)  $^ -o $@ $(SYSREPO_LFLAG) $(YANG_LFLAG) $(DL_LFLAG)
	@echo "Done"

clean:
	rm -rf $(BINDIR)*.o $(BINDIR)*.so $(BINDIR)ruapp $(APPOBJ)*.o


