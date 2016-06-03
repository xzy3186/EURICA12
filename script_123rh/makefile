#OBJ = DSSD2Tr_March TSCorrSiGe DSSDGeMerge separate_March BuildDecay DSSDGeCorr PLASTIC2Tr
#OBJ = online_DSSD WASABI2Tr
OBJ = WASABI2Tr DSSDGeMerge TSCorrBeamEURICA separate BuildDecay MakeWASABITree MakeGGMatrix MakeGGMatrixDecay


all:$(OBJ)

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -Wall -O2 -fno-inline -fPIC -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib -lXMLParser -lanaroot
MYLIB = -I/home/ribf10/analysis/users/xuzy/include -L/home/ribf10/analysis/users/xuzy/include -lDecayEvent

GXX = g++

WASABI2Tr: WASABI2Tr.cpp wasabi_treeinfo.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ WASABI2Tr.cpp

DSSDGeMerge: DSSDGeMerge.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ DSSDGeMerge.cpp

TSCorrBeamEURICA: TSCorrBeamEURICA.cpp wasabi_treeinfo.h eurica.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ TSCorrBeamEURICA.cpp

separate: separate.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h beta.h ion.h BIGRIPS.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ separate.cpp

BuildDecay: BuildDecay.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h beta.h ion.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(MYLIB) -o $@ BuildDecay.cpp

MakeWASABITree: MakeWASABITree.cpp wasabi_treeinfo.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeWASABITree.cpp

MakeGGMatrix: MakeGGMatrix.cpp ion.h zedcoeff.input
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeGGMatrix.cpp

MakeGGMatrixDecay: MakeGGMatrixDecay.cpp gamma_gamma.h zedcoeff.input
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeGGMatrixDecay.cpp

.cpp.o:
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) -c $<

clean:
	rm -f *~ *.o $(OBJ)
