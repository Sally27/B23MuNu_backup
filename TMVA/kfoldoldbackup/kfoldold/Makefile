
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

LCGBOOST = /usr/local
BOOST_INC_DIR  = -I$(LCGBOOST)/include/
BOOST_LIB_OPT  = -L$(LCGBOOST)/lib -lboost_program_options
#BOOST_INC_DIR  = -I/usr/local/include/
#BOOST_LIB_OPT  = -L/usr/local/lib -lboost_program_options


FLAGS   = -O3 -Wall -fPIC -D__ROOFIT_NOBANNER -std=c++0x
INCLUDE = -I$(INCDIR) $(BOOST_INC_DIR) -I$(TMVALOC)

ROOT_FLAGS   = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT_LIBS    = $(shell $(ROOTSYS)/bin/root-config --libs) -lTreePlayer -lTreeViewer -lMinuit -lXMLIO -lMLP -lRIO -lTMVA
ROOFIT_LIBS  = ${ROOT_LIBS} -lRooFitCore -lRooFit -lRooStats -lTreePlayer -lTreeViewer 
#ROOFIT_LIBS += -L$(TMVALOC)/lib/ -lTMVA

FLAGS       += ${INCLUDE} -I$(INCDIR)
FLAGS       += ${ROOT_FLAGS} -lRooFitCore -lRooFit -lRooStats ${BOOST_LIB_OPT} ${BOOST_INC_DIR}
#FLAGS       += ${ROOT_FLAGS} ${BOOST_LIB_OPT} ${BOOST_INC_DIR}
#LIBS         = ${ROOFIT_LIBS}
LIBS         = ${ROOT_LIBS} ${BOOST_LIB_OPT}
#FLAGS       += ${ROOT_LIBS}

USERLIBS += -L/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib -lDendrology
ROOFIT_LIBS += $(USERLIBS)
FLAGS += $(USERLIBS)
#LIBS += $(USERLIBS)
#/vols/lhcbdisk05/ss4314/TMVA/dendrology-master
USERINCLUDES += -I/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/include
FLAGS += $(USERINCLUDES)

LDFLAGS    = $(FLAGS) -shared

# Build a list of srcs and bins to build
SRCS=$(filter-out $(wildcard $(SRCDIR)/_*), $(wildcard $(SRCDIR)/*.cpp))
EXES=$(filter-out $(wildcard $(SRCDIR)/_*), $(wildcard $(SRCDIR)/*.cc))
BINS=$(subst $(SRCDIR), $(EXEDIR),$(subst .cc,,$(EXES)))
BRSS=$(subst $(SRCDIR), $(EXEDIR),$(subst .cpp,,$(EXES)))
OBJS_HPP+=$(subst $(SRCDIR), $(OBJDIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))
OBJS_EXE+=$(subst $(SRCDIR), $(OBJDIR),$(subst cc,$(OBJ_EXT),$(EXES)))
INCS+=$(subst $(SRCDIR), $(OBJDIR),$(subst cpp,$(OBJ_EXT),$(SRCS)))


#all : $(OBJS_EXE) $(OBJS_HPP) $(BINS)
all :  $(SRCS) $(OBJS_HPP) $(OBJS_EXE) $(BINS)

#lib
#all : $(OBJS_HPP) $(SRCS) $(OBJS_EXE) $(BINS)
#kfold : $(OBJDIR)/%.o
#	$(CXX) $(FLAGS) -o kfold $(OBJDIR)/%.o

$(SRCDIR)/%.cpp : $(INCDIR)/%.hpp

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(FLAGS) -c $^ -o $@  $(ROOFIT_LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CXX) $(FLAGS) -c $^ -o $@ $(ROOFIT_LIBS)

$(BINDIR)/%: $(OBJS_HPP) $(OBJDIR)/%.o
	$(CXX) $(FLAGS) -o $@ -g $^ $(ROOFIT_LIBS)


#$(LIBDIR)/libKFold.so: $(OBJS_HPP)
#	$(CXX) $(LDFLAGS) $(LIBS) $(OBJS_HPP) -o $(LIBDIR)/libKFold.so

#lib: $(LIBDIR)/libKFold.so


.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o $(BINDIR)/* 

info:
	@echo EXES $(EXES)
	@echo BINS $(BINS)
	@echo EXES $(EXES)
	@echo OBJS $(OBJS)
	@echo OBJH $(OBJH)

