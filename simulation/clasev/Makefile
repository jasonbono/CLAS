.PHONY: clean

CC = gfortran
AR = ar
C_FLAGS = -O2  -m32 -c 

INCLUDE = -I./ 

SOURCES = $(shell ls *.F)
OBJECTS = $(SOURCES:.F=.o)

all: libfastmc.a

libfastmc.a: $(OBJECTS)
	$(AR) r libfastmc.a $(OBJECTS)

%.o: %.F
	$(CC) -c $(C_FLAGS) $(INCLUDE) $<

clean:
	rm -rf *.o *.a
