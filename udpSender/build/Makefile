#######################################
#
#   Makefile for K23-a:Part1
#

EXE=run-d

ROOTSRC=../src/

MKDIR_P=mkdir -p
OUTDIR=../obj/

GCC=gcc
GCCFLAGS=-Wall -O2 -g -o

CIN=-I ../include

#libraries included folders
CINLIB= \
	-I ../libs/include

STANDARD_LIBS= 

#debug level
ifeq ($(D),error)
	DEBUG_LEVEL=1
	C99=-std=c99
else 
	ifeq ($(D),trace)
		DEBUG_LEVEL=2
		C99=--std=c99
	else
		ifeq ($(D),all)
			DEBUG_LEVEL=3
			C99=--std=c99
		else
			DEBUG_LEVEL=0
		endif
	endif
endif

#precompile variables
DFLAGS=-DDEBUG_LEVEL=$(DEBUG_LEVEL)

#Source file parameters
SRC_C := $(wildcard $(ROOTSRC)*.c)
SRC_O := $(patsubst $(ROOTSRC)%.c, %.o,$(SRC_C))

# Targets 
all: default

default: obj $(EXE)

run: obj $(EXE)
	./$(EXE)

memtest: obj $(EXE)
	valgrind --leak-check=yes -v --dsymutil=yes ./$(EXE) test:

$(EXE): $(SRC_O)
	$(GCC) $(GCCFLAGS) $(EXE) $(SRC_O) $(STANDARD_LIBS)

obj:
	$(foreach file,$(SRC_C),($(GCC) -c $(file) $(CIN) $(CINLIB) $(DFLAGS) ) ; )

clean:
	$(foreach file,$(SRC_O),(rm -f $(file) );)	
	rm -f $(EXE)
	clear





