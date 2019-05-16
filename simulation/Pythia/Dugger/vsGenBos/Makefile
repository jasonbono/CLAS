.PHONY : env clean

CC = gcc
CC++ = g++
CCF = gfortran
AR = ar
#C_FLAGS = -O2  -Wall -fPIC 
C_FLAGS = -O0  -m64 -fPIC

INCLUDE = -I./ -I$(ROOTSYS)/include -I$(CLAS_PACK)/include -I$(CLAS_PACK)/inc_derived

CLAS_LIBS = -L/home/dugger/lib/Linux64RHEL6/ -lc_bos_io -lbosio -lbos \
-lbankdefs -lrecutl -lclasutil -lonline_dummy -litape -lfputil -lfpack \
-lc_cern -lstdc++ -ldl -lnsl

CERN_LIBS = -L/apps/cernlib/x86_64_rhel6/2005/lib/ \
-lgeant321 -lpawlib -lgraflib -lgrafX11 \
-lpacklib -lmathlib -lkernlib 

ROOT_LIBS = $(shell root-config --libs) 
ROOT_LIBS += -lEG -lEGPythia6

MISC_LIBS = ./libbggenXsec.a

LIBS = $(MISC_LIBS) $(CERN_LIBS) $(ROOT_LIBS) $(CLAS_LIBS)

MAIN_FILES = $(shell ./main_files.sh)
EXECUTABLE = $(basename $(MAIN_FILE))

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = vsGen

SOURCESF = $(shell ls *.F)
OBJECTSF = $(SOURCESF:.F=.o)

SOURCESC = $(shell ls *.c)
OBJECTSC = $(SOURCESF:.c=.o)

all: libbggenXsec.a  $(EXECUTABLE) loadBos.o

$(EXECUTABLE): $(OBJECTS) libbggenXsec.a loadBos.o
	$(CC++) $(C_FLAGS) $^ -o $@ $(LIBS)

libbggenXsec.a: $(OBJECTSF)
	$(AR) r libbggenXsec.a $(OBJECTSF)

#libbggenXsec.a:  $(OBJECTSF)

%.o: %.F
	$(CCF) -c $(C_FLAGS) $(INCLUDE) $<

%.o: %.cpp
	$(CC++) -c $(C_FLAGS) $(INCLUDE) $<

%.o: %.c
	$(CC) -c $(C_FLAGS) $(INCLUDE) $<

clean:
	rm -rf *.o *.a $(EXECUTABLE)

env:
	@echo CC++ = $(CC++)
	@echo CCF = $(CCF)
	@echo C_FLAGS = $(C_FLAGS)
	@echo MAIN_FILE = $(MAIN_FILE)
	@echo EXECUTABLE = $(EXECUTABLE)
	@echo SOURCES = $(SOURCES)
	@echo SOURCESF = $(SOURCESF)
	@echo OBJECTS = $(OBJECTS)
	@echo OBJECTSF = $(OBJECTSF)
	@echo INCLUDE = $(INCLUDE)
	@echo LIBS = $(LIBS)
