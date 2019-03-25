## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFLAGS = -Wall -g -DLINUX
LFLAGS = -lglut -L/usr/lib -L/usr/X11R6/lib -lXi -lXmu -lGL -lGLU -lm

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
  assn1.cpp \
	line.cpp \
	curve.cpp \
	$(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): assn1.o line.o curve.o
	$(CC) -o assn1 assn1.o line.o curve.o ${LFLAGS}

depend :
	makedepend ${PROGFILES}

clean:
	rm *.o
	rm assn1

# DO NOT DELETE
