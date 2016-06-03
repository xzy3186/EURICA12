CCX = g++ -O2 -DWARNING_MSG -DREDUCETREE #-DCOMPTONCAL
LD  = g++

CFLAGS  = -c -Wall -fPIC
LDFLAGS = $(shell root-config --ldflags) -O2 -fPIC
SOFLAGS = -shared

SOLIB       = libDecayEvent.so

LIBS     =  $(shell root-config --glibs) -lrt
INCLUDES = -I$(shell root-config --incdir)

# Assume a cpp file for each header file
HEADERFILES = DecayEvent.h

HDRS    = DecayEvent.h LinkDef.h
SOURCES = Dictionary.cxx DecayEvent.cxx
OBJECTS = Dictionary.o DecayEvent.o

all: $(SOURCES) $(SOLIB)

# The variable $@ has the value of the target. In this case ${@} = Rising.so
$(SOLIB): $(OBJECTS)
	$(LD) $(LDFLAGS) $(SOFLAGS) $(LIBS) $(OBJECTS) -o $@
	@echo "$@ done"

%.o: %.cxx $(HEADERFILES) Makefile
	$(CCX) $(CFLAGS) $(INCLUDES) $<

Dictionary.cxx Dictionary.h: ${HDRS}
	rootcint -f Dictionary.cxx -c ${INCLUDES} ${HDRS}

clean:
	rm -f *.o Dictionary.cxx Dictionary.h *.so
