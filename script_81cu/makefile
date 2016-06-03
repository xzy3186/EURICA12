#OBJ = DSSD2Tr_March TSCorrSiGe DSSDGeMerge separate_March BuildDecay DSSDGeCorr PLASTIC2Tr
#OBJ = online_DSSD WASABI2Tr
OBJ = WASABI2Tr DSSDGeMerge TSCorrSiGe TSCorrBeamEURICA separate BuildDecay BuildDecay_Select2 BuildDecay_Select3 MakeGGMatrixDecayOneIsotope2 MakeGGMatrixOneIsotope MakeGGMatrix


all:$(OBJ)

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -Wall -O2 -fno-inline -fPIC -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib -lXMLParser -lanaroot
MYLIB = -I/home/analysis/analysis/anaroot/users/xuzy-decay/include -L/home/analysis/analysis/anaroot/users/xuzy-decay/include -lDecayEvent

GXX = g++

WASABI2Tr: WASABI2Tr.cpp wasabi_treeinfo.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ WASABI2Tr.cpp

DSSDGeMerge: DSSDGeMerge.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ DSSDGeMerge.cpp

TSCorrSiGe: TSCorrSiGe.cpp wasabi_treeinfo.h eurica.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ TSCorrSiGe.cpp

TSCorrBeamEURICA: TSCorrBeamEURICA.cpp wasabi_treeinfo.h eurica.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ TSCorrBeamEURICA.cpp

separate: separate.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h beta.h ion.h BIGRIPS.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ separate.cpp

BuildDecay: BuildDecay.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h beta.h ion.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(MYLIB) -o $@ BuildDecay.cpp

BuildDecay_Select2: BuildDecay_Select2.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h beta.h ion.h decay_ggmatrix.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(MYLIB) -o $@ BuildDecay_Select2.cpp

BuildDecay_Select3: BuildDecay_Select3.cpp wasabi_treeinfo.h eurica.h eurica_wasabi.h beta.h ion.h decay_ggmatrix.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(MYLIB) -o $@ BuildDecay_Select3.cpp

#MakeWASABITree: MakeWASABITree.cpp wasabi_treeinfo.h
#	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeWASABITree.cpp
#
MakeGGMatrix: MakeGGMatrix.cpp ion.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeGGMatrix.cpp
#
#MakeGGMatrixDecay: MakeGGMatrixDecay.cpp decay_ggmatrix.h zedcoeff.input
#	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeGGMatrixDecay.cpp
#
MakeGGMatrixDecayOneIsotope2: MakeGGMatrixDecayOneIsotope2.cpp decay_ggmatrix.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeGGMatrixDecayOneIsotope2.cpp
MakeGGMatrixOneIsotope: MakeGGMatrixOneIsotope.cpp decay_ggmatrix.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $@ MakeGGMatrixOneIsotope.cpp

.cpp.o:
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) -c $<

clean:
	rm -f *~ *.o $(OBJ)
