# Keerthana Ramesh
# SE 3377.501
# kxr144230@utdallas.edu
 

CXX = g++
CXXFLAGS =
CPPFLAGS = -std=c++11 -Wall -g -I/people/cs/s/sxp127930/include
LDFLAGS = -L/people/cs/s/sxp127930/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = cdkexample

OBJS = example1.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

