
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

#LCGBOOST = /usr/local
#BOOST_INC_DIR  = -I$(LCGBOOST)/include/
#BOOST_LIB_OPT  = -L$(LCGBOOST)/lib -lboost_program_options
#BOOST_INC_DIR  = -I/usr/local/include/
#BOOST_LIB_OPT  = -L/usr/local/lib -lboost_program_options


FLAGS   = -O3 -Wall -fPIC -D__ROOFIT_NOBANNER -std=c++0x
INCLUDE = -I$(INCDIR) $(BOOST_INC_DIR) -I$(TMVALOC)

ROOT_FLAGS   = $(shell $(ROOTSYS)/bin/root-config --cflags)
#ROOT_LIBS = -L$(TMVALOC)/lib/ -lTMVA
ROOT_LIBS = $(shell $(ROOTSYS)/bin/root-config --libs) -lTreePlayer -lTreeViewer -lMinuit -lXMLIO -lMLP -lRIO 
#-lTMVA
ROOFIT_LIBS  = ${ROOT_LIBS} -lm -lRooFitCore -lRooFit -lRooStats -lTreePlayer -lTreeViewer 
#ROOFIT_LIBS += -L$(TMVALOC)/lib/ -lTMVA
#ROOT_LIBS += $(TMVALOC)/lib/ 

ROOT_FLAGS   = $(shell $(ROOTSYS)/bin/root-config --cflags) -D__ROOFIT_NOBANNER
ROOT_LIBS    = $(shell $(ROOTSYS)/bin/root-config --libs) -lTreePlayer -lTreeViewer -lMinuit -lXMLIO -lMLP -lRIO -lTMVA

FLAGS = $(ROOT_FLAGS)

FLAGS += -I$(INCDIR)
FLAGS       += ${INCLUDE} -I$(INCDIR)
FLAGS       += ${ROOT_FLAGS} -lRooFitCore -lRooFit -lRooStats ${BOOST_LIB_OPT} ${BOOST_INC_DIR}
#FLAGS       += ${ROOT_FLAGS} ${BOOST_LIB_OPT} ${BOOST_INC_DIR}
#LIBS         = ${ROOFIT_LIBS}
LIBS         = ${ROOT_LIBS} ${BOOST_LIB_OPT}
#FLAGS       += ${ROOT_LIBS}
#USERLIBS = -L/vols/lhcb/ss4314/adapttbcode/kfold/lib -lKFold
#USERLIBS += -L/vols/lhcb/ss4314/TMVA/dendrology-master/lib -lDendrology
#USERLIBS += -L/vols/lhcb/ss4314/TMVA/dendrology-master/lib -lDendrology

ROOT_LIBS += $(USERLIBS)
FLAGS += $(USERLIBS)

#FLAGS += -I/vols/lhcb/ss4314/adapttbcode/kfold/include
#FLAGS += -I/vols/lhcb/ss4314/TMVA/dendrology-master/include

#Sally rem USERLIBS += -L/home/hep/th1011/Documents/Kee/customRoofitClasses/lib -lcustomroofit
#USERLIBS += -L$(TMVALOC)/lib -lTMVA
ROOFIT_LIBS += $(USERLIBS)
FLAGS += $(USERLIBS)
#LIBS += $(USERLIBS)

#Sally remUSERINCLUDES += -I/home/hep/th1011/Documents/Kee/customRoofitClasses/include
FLAGS += $(USERINCLUDES) -fPIC

LDFLAGS    = $(FLAGS) -shared

# Build a list of srcs and bins to build
SRCS=$(filter-out $(wildcard $(SRCDIR)/_*), $(wildcard $(SRCDIR)/*.cpp))      #select all .cpp as source files
EXES=$(filter-out $(wildcard $(SRCDIR)/_*), $(wildcard $(SRCDIR)/*.cc))			#select all .cc as "mains"
BINS=$(subst $(SRCDIR), $(EXEDIR),$(subst .cc,,$(EXES)))								#create the executable names by removing the .cc, and puting them in the executable dir
BRSS=$(subst $(SRCDIR), $(EXEDIR),$(subst .cpp,,$(EXES)))
OBJS_HPP+=$(subst $(SRCDIR), $(OBJDIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))			#create all the object file name by removing the .cpp and adding a .o
OBJS_EXE+=$(subst $(SRCDIR), $(OBJDIR),$(subst cc,$(OBJ_EXT),$(EXES)))
INCS+=$(subst $(SRCDIR), $(OBJDIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))				


#all : $(OBJS_EXE) $(OBJS_HPP) $(BINS)
all : $(SRCS) $(OBJS_HPP) $(OBJS_EXE) $(BINS) lib
#all : $(OBJS_HPP) $(SRCS) $(OBJS_EXE) $(BINS)

$(SRCDIR)/%.cpp : $(INCDIR)/%.hpp

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(FLAGS) -c $^ -o $@  $(ROOFIT_LIBS) 

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CXX) $(FLAGS) -c $^ -o $@ $(ROOFIT_LIBS)

$(BINDIR)/%: $(OBJS_HPP) $(OBJDIR)/%.o
	$(CXX) $(FLAGS) -o $@ -g $^ $(ROOFIT_LIBS)

$(LIBDIR)/libERROR.so: $(OBJS_HPP)
	$(CXX) $(LDFLAGS) $(LIBS) $(OBJS_HPP) -o $(LIBDIR)/libERROR.so

lib: $(LIBDIR)/libERROR.so


.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o $(BINDIR)/* 

info:
	@echo EXES $(EXES)
	@echo BINS $(BINS)
	@echo EXES $(EXES)
	@echo OBJS $(OBJS)
	@echo OBJH $(OBJH)

