CXX = g++

BASEDIR = $(shell pwd)
LIBDIR = $(BASEDIR)/lib
EXEDIR = $(BASEDIR)/bin
SRCDIR = $(BASEDIR)/src
OBJDIR = $(BASEDIR)/obj
INCDIR = $(BASEDIR)/include

ROOT_FLAGS   = $(shell $(ROOTSYS)/bin/root-config --cflags) -D__ROOFIT_NOBANNER
ROOT_LIBS    = $(shell $(ROOTSYS)/bin/root-config --libs) -lTreePlayer -lTreeViewer -lMinuit -lXMLIO -lMLP -lRIO -lTMVA 

FLAGS = $(ROOT_FLAGS)


FLAGS += -I$(INCDIR)
USERLIBS = -L/vols/lhcbdisk05/ss4314/codetoinvestigate/kfold/lib -lKFold
#USERLIBS += -L/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib -lDendrology
USERLIBS += -L/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib -lDendrology

ROOT_LIBS += $(USERLIBS)
FLAGS += $(USERLIBS)

FLAGS += -I/vols/lhcbdisk05/ss4314/codetoinvestigate/kfold/lib
FLAGS += -I/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/include

ROOFIT_LIBS  = ${ROOT_LIBS} -lRooFitCore -lRooFit -lRooStats -lTreePlayer -lTreeViewer
ROOFIT_LIBS += $(USERLIBS)


all: main

main: $(OBJDIR)/main.o $(OBJDIR)/reweightingTools.o $(OBJDIR)/usefulFunctions.o
	$(CXX) $(FLAGS) -o main $(OBJDIR)/main.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o $(ROOFIT_LIBS)

$(OBJDIR)/main.o : $(SRCDIR)/mainPerformReweighting.cc $(INCDIR)/reweightingTools.h $(INCDIR)/usefulFunctions.hpp 
	$(CXX) $(FLAGS) -c $(SRCDIR)/mainPerformReweighting.cc -o $(OBJDIR)/main.o  $(ROOFIT_LIBS)

$(OBJDIR)/reweightingTools.o : $(SRCDIR)/reweightingTools.cpp $(INCDIR)/reweightingTools.h $(INCDIR)/usefulFunctions.hpp
	$(CXX) $(FLAGS) -c $(SRCDIR)/reweightingTools.cpp -o $(OBJDIR)/reweightingTools.o $(ROOFIT_LIBS)

$(OBJDIR)/usefulFunctions.o : $(SRCDIR)/usefulFunctions.cpp $(INCDIR)/usefulFunctions.hpp
	$(CXX) $(FLAGS) -c $(SRCDIR)/usefulFunctions.cpp -o $(OBJDIR)/usefulFunctions.o $(ROOFIT_LIBS)

#$(OBJDIR)/plotBDT.o : $(SRCDIR)/plotBDT.cc $(INCDIR)/plotBDT.h
#	$(CXX) $(FLAGS) -c $(SRCDIR)/plotBDT.cc -o $(OBJDIR)/plotBDT.o $(ROOT_LIBS)


.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o
