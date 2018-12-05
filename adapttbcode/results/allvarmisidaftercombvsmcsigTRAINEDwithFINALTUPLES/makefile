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
USERLIBS = -L/vols/lhcbdisk05/ss4314/adapttbcode/kfold/lib -lKFold
#USERLIBS += -L/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib -lDendrology
USERLIBS += -L/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib -lDendrology

ROOT_LIBS += $(USERLIBS)
FLAGS += $(USERLIBS)

FLAGS += -I/vols/lhcbdisk05/ss4314/adapttbcode/kfold/include 
FLAGS += -I/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/include

all: main 
#mainCascades mainSeparateTraining mainOptimiseBDT mainCrap

#main: $(OBJDIR)/main.o $(OBJDIR)/usefulFunctions.o
#	$(CXX) $(FLAGS) -o main $(OBJDIR)/main.o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

main: $(OBJDIR)/main.o $(OBJDIR)/Lenin4.o $(OBJDIR)/usefulFunctions.o
	$(CXX) $(FLAGS) -o main $(OBJDIR)/main.o $(OBJDIR)/Lenin4.o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

$(OBJDIR)/main.o : $(SRCDIR)/main.cc $(INCDIR)/Lenin4.h $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/main.cc -o $(OBJDIR)/main.o  $(ROOT_LIBS)


$(OBJDIR)/Lenin4.o : $(SRCDIR)/Lenin4.cc $(INCDIR)/Lenin4.h $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/Lenin4.cc -o $(OBJDIR)/Lenin4.o $(ROOT_LIBS)


#mainCascades: $(OBJDIR)/mainCascades.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o
#	$(CXX) $(FLAGS) -o mainCascades $(OBJDIR)/mainCascades.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

#mainSeparateTraining: $(OBJDIR)/mainSeparateTraining.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o
#	$(CXX) $(FLAGS) -o mainSeparateTraining $(OBJDIR)/mainSeparateTraining.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

#mainOptimiseBDT: $(OBJDIR)/mainOptimiseBDT.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o
#	$(CXX) $(FLAGS) -o mainOptimiseBDT $(OBJDIR)/mainOptimiseBDT.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

#mainCrap: $(OBJDIR)/mainCrap.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o
#	$(CXX) $(FLAGS) -o mainCrap $(OBJDIR)/mainCrap.o $(OBJDIR)/make_mc_true_tree.o $(OBJDIR)/prepare_tree.o $(OBJDIR)/getPreselection.o $(OBJDIR)/plotBDT.o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)
	
#$(OBJDIR)/main.o : $(SRCDIR)/main.cc $(INCDIR)/usefulFunctions.h 
#	$(CXX) $(FLAGS) -c $(SRCDIR)/main.cc -o $(OBJDIR)/main.o  $(ROOT_LIBS)

#$(OBJDIR)/mainCascades.o : $(SRCDIR)/mainCascades.cc $(INCDIR)/make_mc_true_tree.h $(INCDIR)/prepare_tree.h $(INCDIR)/getPreselection.h $(INCDIR)/plotBDT.h $(INCDIR)/usefulFunctions.h 
#	$(CXX) $(FLAGS) -c $(SRCDIR)/mainCascades.cc -o $(OBJDIR)/mainCascades.o  $(ROOT_LIBS)

#$(OBJDIR)/mainSeparateTraining.o : $(SRCDIR)/mainSeparateTraining.cc $(INCDIR)/make_mc_true_tree.h $(INCDIR)/prepare_tree.h $(INCDIR)/getPreselection.h $(INCDIR)/plotBDT.h $(INCDIR)/usefulFunctions.h 
#	$(CXX) $(FLAGS) -c $(SRCDIR)/mainSeparateTraining.cc -o $(OBJDIR)/mainSeparateTraining.o  $(ROOT_LIBS)

#$(OBJDIR)/mainOptimiseBDT.o : $(SRCDIR)/mainOptimiseBDT.cc $(INCDIR)/make_mc_true_tree.h $(INCDIR)/prepare_tree.h $(INCDIR)/getPreselection.h $(INCDIR)/plotBDT.h $(INCDIR)/usefulFunctions.h 
#	$(CXX) $(FLAGS) -c $(SRCDIR)/mainOptimiseBDT.cc -o $(OBJDIR)/mainOptimiseBDT.o  $(ROOT_LIBS)

#$(OBJDIR)/mainCrap.o : $(SRCDIR)/mainCrap.cc $(INCDIR)/make_mc_true_tree.h $(INCDIR)/prepare_tree.h $(INCDIR)/getPreselection.h $(INCDIR)/plotBDT.h $(INCDIR)/usefulFunctions.h 
#	$(CXX) $(FLAGS) -c $(SRCDIR)/mainCrap.cc -o $(OBJDIR)/mainCrap.o  $(ROOT_LIBS)

#$(OBJDIR)/prepare_tree.o : $(SRCDIR)/prepare_tree.cc $(INCDIR)/prepare_tree.h $(INCDIR)/usefulFunctions.h
#	$(CXX) $(FLAGS) -c $(SRCDIR)/prepare_tree.cc -o $(OBJDIR)/prepare_tree.o $(ROOT_LIBS)
	
#$(OBJDIR)/make_mc_true_tree.o : $(SRCDIR)/make_mc_true_tree.cc $(INCDIR)/make_mc_true_tree.h
#	$(CXX) $(FLAGS) -c $(SRCDIR)/make_mc_true_tree.cc -o $(OBJDIR)/make_mc_true_tree.o $(ROOT_LIBS)

#$(OBJDIR)/getPreselection.o : $(SRCDIR)/getPreselection.cc $(INCDIR)/getPreselection.h $(INCDIR)/usefulFunctions.h
#	$(CXX) $(FLAGS) -c $(SRCDIR)/getPreselection.cc -o $(OBJDIR)/getPreselection.o $(ROOT_LIBS)

#$(OBJDIR)/plotBDT.o : $(SRCDIR)/plotBDT.cc $(INCDIR)/plotBDT.h $(INCDIR)/getPreselection.h
#	$(CXX) $(FLAGS) -c $(SRCDIR)/plotBDT.cc -o $(OBJDIR)/plotBDT.o $(ROOT_LIBS)

$(OBJDIR)/usefulFunctions.o : $(SRCDIR)/usefulFunctions.cc $(INCDIR)/usefulFunctions.h
	$(CXX) $(FLAGS) -c $(SRCDIR)/usefulFunctions.cc -o $(OBJDIR)/usefulFunctions.o $(ROOT_LIBS)

.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o
