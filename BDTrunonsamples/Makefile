
CXX      = g++

#BIN_DIR = bin
#LIB_DIR = lib
#OBJ_DIR = obj
#SRC_DIR = src
#INC_DIR = include

# A list of directories
BASEDIR = $(shell pwd)
LIBDIR = $(BASEDIR)/lib
EXEDIR = $(BASEDIR)/bin
BINDIR = $(BASEDIR)/bin
SRCDIR = $(BASEDIR)/src
OBJDIR = $(BASEDIR)/obj
INCDIR = $(BASEDIR)/include
#TESTDIR = $(BASEDIR)/test
DOCDIR= $(BASEDIR)/docs
OBJ_EXT=o

#LCG_external_area = /afs/cern.ch/sw/lcg/external
#LCGBOOST = $(LCG_external_area)/Boost/1.48.0_python2.6/x86_64-slc5-gcc46-opt
#BOOST_INC_DIR  = -I$(LCGBOOST)/include/
#BOOST_LIB_OPT  = -L$(LCGBOOST)/lib -lboost_program_options
#BOOST_INC_DIR  = -I/usr/include/
#BOOST_LIB_OPT  = -L/usr/lib64 -lboost_program_options
BOOST_INC_DIR  = -I/usr/local/include/
BOOST_LIB_OPT  = -L/usr/local/lib -lboost_program_options -lgsl -lgslcblas


FLAGS   = -O3 -Wall -fPIC -D__ROOFIT_NOBANNER -std=c++0x
INCLUDE = -I$(INCDIR) $(BOOST_INC_DIR) -I$(TMVALOC)
INCLUDE += -I/vols/lhcb/ss4314/TMVA/kfoldandubdt/optimizedubdt/uboost/TMVA-v4.1.2/inc


ROOT_FLAGS   = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT_LIBS    = $(shell $(ROOTSYS)/bin/root-config --libs) -lTreePlayer -lTreeViewer -lMinuit -lXMLIO -lMLP -lRIO
ROOFIT_LIBS  = ${ROOT_LIBS} -lRooFitCore -lRooFit -lRooStats -lTreePlayer -lTreeViewer
ROOFIT_LIBS += -L$(TMVALOC)/lib/ -lTMVA

FLAGS       += ${INCLUDE} -I$(INCDIR)
FLAGS       += ${ROOT_FLAGS} -lRooFitCore -lRooFit -lRooStats ${BOOST_LIB_OPT} ${BOOST_INC_DIR}
#FLAGS       += ${ROOT_FLAGS} ${BOOST_LIB_OPT} ${BOOST_INC_DIR}
#LIBS         = ${ROOFIT_LIBS}
LIBS         = ${ROOT_LIBS} ${BOOST_LIB_OPT}
#FLAGS       += ${ROOT_LIBS}

#SCPHDIR = /vols/lhcbdisk04/shall/Scph/
#SCPHDIR = $(HOME)/work/Scph/
#USERINCLUDES += -I$(SCPHDIR)/Easel/include/
#USERINCLUDES += -I$(SCPHDIR)/Knives/include/
#USERINCLUDES += -I$(SCPHDIR)/Stools/include/
#USERINCLUDES += -I$(SCPHDIR)/Dendrology/include/
#USERINCLUDES += -I$(SCPHDIR)/Monkey/include/
#USERINCLUDES += -I$(HOME)/work/inflaton/DBClasses/include/
#FLAGS += $(USERINCLUDES)


USERLIBS += -L/vols/lhcb/ss4314/TMVA/dendrology-master/lib -lDendrology
ROOFIT_LIBS += $(USERLIBS)
FLAGS += $(USERLIBS)
#LIBS += $(USERLIBS)
#/vols/lhcb/ss4314/TMVA/dendrology-master
USERINCLUDES += -I/vols/lhcb/ss4314/TMVA/dendrology-master/include
FLAGS += $(USERINCLUDES)

LDFLAGS    = $(FLAGS) -shared




#USERLIBS += -L$(SCPHDIR)/lib -lKnives -lStools -lEasel -lDendrology -lMonkey
#USERLIBS += -L$(HOME)/work/inflaton/DBClasses/lib/ -lDBClasses
#-lAnalyses -lCustomRooFit
#-lSMVA
#ROOFIT_LIBS += $(USERLIBS)

# Build a list of srcs and bins to build
SRCS=$(filter-out $(wildcard $(SRCDIR)/_*), $(wildcard $(SRCDIR)/*.cpp))
EXES=$(filter-out $(wildcard $(SRCDIR)/_*), $(wildcard $(SRCDIR)/*.cc))
BINS=$(subst $(SRCDIR), $(EXEDIR),$(subst .cc,,$(EXES)))
BRSS=$(subst $(SRCDIR), $(EXEDIR),$(subst .cpp,,$(EXES)))
OBJS_HPP+=$(subst $(SRCDIR), $(OBJDIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))
OBJS_EXE+=$(subst $(SRCDIR), $(OBJDIR),$(subst cc,$(OBJ_EXT),$(EXES)))
INCS+=$(subst $(SRCDIR), $(OBJDIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))


#all : $(OBJS_EXE) $(OBJS_HPP) $(BINS)
all : $(SRCS) $(OBJS_HPP) $(OBJS_EXE) $(BINS)
#all : $(OBJS_HPP) $(SRCS) $(OBJS_EXE) $(BINS)

$(SRCDIR)/%.cpp : $(INCDIR)/%.hpp

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(FLAGS) -c $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CXX) $(FLAGS) -c $^ -o $@

$(BINDIR)/%: $(OBJS_HPP) $(OBJDIR)/%.o
	$(CXX) $(FLAGS) -o $@ -g $^ $(ROOFIT_LIBS)



.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o $(BINDIR)/* *.C

info:
	@echo EXES $(EXES)
	@echo BINS $(BINS)
	@echo EXES $(EXES)
	@echo OBJS $(OBJS)
	@echo OBJH $(OBJH)

