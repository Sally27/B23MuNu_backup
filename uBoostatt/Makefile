# 
# Makefile for programs that include ROOT
# 
ROOTCFLAGS   := $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS     := $(shell $(ROOTSYS)/bin/root-config --libs)

CXXFLAGS      = -O -Wall -fPIC -g -W
CXXFLAGS     += $(ROOTCFLAGS) 

LIBS 	  = $(ROOTLIBS) -lTreePlayer -lRooFitCore -lRooFit -lMinuit -lFoam -lXMLIO 
LIBS	      += -L/vols/lhcbdisk05/ss4314/uBoostatt/TMVA-v4.1.2/lib -lTMVA 

CC            = c++
EXECUTABLE    = uBoostTrain
BINDIR        = ${PWD}/#/bin/
SRCDIR        = ${PWD}/#src/
OBJS	      = $(BINDIR)uBoostTrain.o 
INCLUDES += -I/vols/lhcbdisk05/ss4314/uBoostatt/TMVA-v4.1.2/inc
CXXFLAGS += $(INCLUDES)

#CC            = c++
EXECUTABLE2    = uBoostEval
#BINDIR        = ${PWD}/#/bin/
#SRCDIR        = ${PWD}/#src/
OBJS2          = $(BINDIR)uBoostEval.o
#INCLUDES += -I/afs/cern.ch/work/s/slstefko/samstmva/uBoost_v2/TMVA-v4.1.2/inc
#CXXFLAGS += $(INCLUDES)

#-------------------------------------------------------------
$(EXECUTABLE) :     $(OBJS) 
				c++ $(LIBS) -lTMVA -L/vols/lhcbdisk05/ss4314/uBoostatt/TMVA-v4.1.2/lib -o $(BINDIR)$(EXECUTABLE) $(OBJS) 

$(EXECUTABLE2) :     $(OBJS2)
				c++ $(LIBS) -lTMVA -L/vols/lhcbdisk05/ss4314/uBoostatt/TMVA-v4.1.2/lib -o $(BINDIR)$(EXECUTABLE2) $(OBJS2)
#-------------------------------------------------------------


$(BINDIR)uBoostTrain.o : 		$(SRCDIR)uBoostTrain.C
				g++ $(CXXFLAGS) -c  -o $(BINDIR)uBoostTrain.o $(BINDIR)uBoostTrain.C

$(BINDIR)uBoostEval.o :                $(SRCDIR)uBoostEval.C
				g++ $(CXXFLAGS) -c  -o $(BINDIR)uBoostEval.o $(BINDIR)uBoostEval.C

#-------------------------------------------------------
clean:
		@rm -f $(BINDIR)uBoostTrain $(SRCDIR)/*~ core* $(BINDIR)/*.o ./*~ 
		@rm -f $(BINDIR)uBoostTrain $(SRCDIR)/*~ core* $(BINDIR)/*.o ./*~ 
#		@rmdir $(BINDIR)
# DO NOT DELETE
