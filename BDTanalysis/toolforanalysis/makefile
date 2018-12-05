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
USERLIBS = -L/vols/lhcbdisk05/ss4314/TMVA/kfoldold/lib -lKFold
USERLIBS += -L/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib -lDendrology


ROOT_LIBS += $(USERLIBS)
FLAGS += $(USERLIBS)
FLAGS += -I/vols/lhcbdisk05/ss4314/TMVA/kfoldold/include
FLAGS += -I/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/include

all: main

main: $(OBJDIR)/main.o $(OBJDIR)/InverseSigandBkg.o $(OBJDIR)/usefulFunctions.o
	$(CXX) $(FLAGS) -o main $(OBJDIR)/main.o $(OBJDIR)/InverseSigandBkg.o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

$(OBJDIR)/main.o : $(SRCDIR)/main.cc $(INCDIR)/InverseSigandBkg.h $(INCDIR)/usefulFunctions.h 
	$(CXX) $(FLAGS) -c $(SRCDIR)/main.cc -o $(OBJDIR)/main.o  $(ROOT_LIBS)

$(OBJDIR)/Lenin.o : $(SRCDIR)/Lenin.cc $(INCDIR)/Lenin.h $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/Lenin.cc -o $(OBJDIR)/Lenin.o $(ROOT_LIBS)

$(OBJDIR)/Lenin2.o : $(SRCDIR)/Lenin2.cc $(INCDIR)/Lenin2.h $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/Lenin2.cc -o $(OBJDIR)/Lenin2.o $(ROOT_LIBS)

$(OBJDIR)/Lenin3.o : $(SRCDIR)/Lenin3.cc $(INCDIR)/Lenin3.h $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/Lenin3.cc -o $(OBJDIR)/Lenin3.o $(ROOT_LIBS)

$(OBJDIR)/Lenin4.o : $(SRCDIR)/Lenin4.cc $(INCDIR)/Lenin4.h $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/Lenin4.cc -o $(OBJDIR)/Lenin4.o $(ROOT_LIBS)

$(OBJDIR)/InverseSigandBkg.o : $(SRCDIR)/InverseSigandBkg.cc $(INCDIR)/InverseSigandBkg.h $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/InverseSigandBkg.cc -o $(OBJDIR)/InverseSigandBkg.o $(ROOT_LIBS)

$(OBJDIR)/usefulFunctions.o : $(SRCDIR)/usefulFunctions.cc $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/usefulFunctions.cc -o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o
