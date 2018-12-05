# 
# Makefile for programs that include ROOT
# 
ROOTCFLAGS   := $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS     := $(shell $(ROOTSYS)/bin/root-config --libs)

CXXFLAGS      = -O -Wall -fPIC -g -W
CXXFLAGS     += $(ROOTCFLAGS) 

LIBS 				= $(ROOTLIBS) -lTreePlayer -lTMVA -lRooFitCore -lRooFit -lMinuit -lFoam -lXMLIO 
#LIBS	      += -L/afs/cern.ch/user/j/johndan/Analysis/B2DDh/uBDT/TrainBDT/TMVA-v4.1.2/lib -lTMVA 

CC            = c++
EXECUTABLE    = uBoostTrain
BINDIR        = ${PWD}/#/bin/
SRCDIR        = ${PWD}/#src/
OBJS	      = $(BINDIR)uBoostTrain.o 
INCLUDES += -I/afs/cern.ch/work/s/slstefko/samstmva/uBoost_v2/TMVA-v4.1.2/inc
CXXFLAGS += $(INCLUDES)

#-------------------------------------------------------------
$(EXECUTABLE) :     $(OBJS) 
				c++ $(LIBS) -lTMVA -L/afs/cern.ch/work/s/slstefko/samstmva/uBoost_v2/TMVA-v4.1.2/lib -o $(BINDIR)$(EXECUTABLE) $(OBJS) 
#-------------------------------------------------------------


$(BINDIR)uBoostTrain.o : 		$(SRCDIR)uBoostTrain.C
				g++ $(CXXFLAGS) -c  -o $(BINDIR)uBoostTrain.o $(BINDIR)uBoostTrain.C


#-------------------------------------------------------
clean:
		@rm -f $(BINDIR)uBoostTrain $(SRCDIR)/*~ core* $(BINDIR)/*.o ./*~ 
#		@rmdir $(BINDIR)
# DO NOT DELETE
