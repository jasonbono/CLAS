# setup C++ compiler
CXX           = g++

# setup C++ compiler flags
# -O: optimization flag level 1
# -Wall: Warnings (all) 
# -fPIC: generate Position Independent Code for the computer 
CXXFLAGS      = -O -Wall -fPIC

# setup linker
LD            = g++

# setup linker flags
# -O optimization flag level 1
LDFLAGS       = -O

# shared objects linking flag
SOFLAGS       = -shared

# Warning option set to not warn about using deprecated features
WNO          = -Wno-deprecated

# ROOT specific flags and libraries
# run the command 'root-config --cflags' in a shell and store its output
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

# additional ROOT graphics library for linking
TSpectrum     = -lSpectrum

# combine necessary flags and options into one variable
CXXFLAGS     += $(ROOTCFLAGS)
CXXFLAGS     += $(WNO)

# add all libraries, options and paths
SYSLIBS       = 
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) -L/usr/local/lib/ $(SYSLIBS) 

# add precompiled fortran libraries  
GLIBS         += ccylinder.o intersept.o targcell.o stcounter.o
# the gfortran library is required for compiling against fortran libraries 
# the path of the fortran library is located in a separate path
GLIBS         += -L/usr/local/gfortran/lib -lgfortran
# add spectrum ROOT graphics library if needed
GLIBS         += $(TSpectrum)

#========================= PROGRAM ==========================================

# setup suffixes for objects, sources, executables, 
# dynamically linked libraries, and dictionaries
ObjSuf        = o
SrcSuf        = cc
ExeSuf        =
DllSuf        = so
DictSuf       = Dict.o

# program specific definitions, objects, source and executable names
BASENAME      = mytest
MAINOBJ       = $(BASENAME).$(ObjSuf)
MAINSOURCE    = $(BASENAME).$(SrcSuf)
MAIN          = $(BASENAME)$(ExeSuf)
# list of programs to build
PROGRAMS      = $(MAIN)

############################ BUILD ##########################################

# define suffix list
.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

# default build action to build all PROGRAMS
# the definition of PROGRAMS is given later
all: $(PROGRAMS)

# documentation build action
doc:
	root.exe -b -q make_html.C

# compile all source files and create corresponding object file
# $< : the name of the first prerequisite (source) file
%.$(ObjSuf):%.$(SrcSuf)
	$(CXX) $(CXXFLAGS) -c $<

# create root dictionaries based on .h files if needed
# $@: the file name of the target of the rule, in this case Dict.cc
%Dict.$(SrcSuf):%.h
	rootcint -f $@ -c $<

# create a libraries based on ROOT dictionary and objects
# $^: names of all prerequisites with spaces between them
# $@: the file name of the target of the rule, in this case lib%.so
lib%.$(DllSuf): %Dict.$(ObjSuf) %.$(ObjSuf)
	$(LD) $(SOFLAGS) $(CXXFLAGS) $^ -o $@

# define main target building schema by linking against necessary libraries
# $^: names of all prerequisites with spaces between them
# $@: the file name of the target of the rule, in this case $(MAIN)
$(MAIN): $(MAINOBJ)
	$(LD) $(CXXFLAGS) $(GLIBS) $^ -o $@

# clean all objects related to main program
clean:  	
		rm -f $(MAINOBJ)

# clean all root dictionaries
distclean:      
		make clean
		@rm -f $(SLIB) *Dict.* *.def
