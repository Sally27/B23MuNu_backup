
CXX      = g++

# A list of directories
BASEDIR = $(shell pwd)
LIBDIR = $(BASEDIR)/lib
EXEDIR = $(BASEDIR)/bin
BINDIR = $(BASEDIR)/bin
SRCDIR = $(BASEDIR)/src
OBJDIR = $(BASEDIR)/obj
INCDIR = $(BASEDIR)/include
DOCDIR= $(BASEDIR)/docs
OBJ_EXT=o

BOOST_INC_DIR  = -I/usr/local/include/
BOOST_LIB_OPT  = -L/usr/local/lib -lboost_program_options


FLAGS   = -O3 -Wall -fPIC -D__ROOFIT_NOBANNER
INCLUDE = -I$(INCDIR) $(BOOST_INC_DIR)

ROOT_FLAGS   = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT_LIBS    = $(shell $(ROOTSYS)/bin/root-config --libs) -lTreePlayer -lMinuit -lXMLIO -lMLP -lRIO

ROOFIT_LIBS  = ${ROOT_LIBS} -lRooFitCore -lRooFit -lRooStats
ROOFIT_LIBS += -L/vols/lhcbdisk05/ss4314/samtmva/uBoost_v2/TMVA-v4.1.2/lib/ -lTMVA
FLAGS       += ${INCLUDE} -I$(INCDIR)
FLAGS       += ${ROOT_FLAGS} -lRooFitCore -lRooFit -lRooStats ${BOOST_LIB_OPT} ${BOOST_INC_DIR}
#FLAGS       += -L/Users/scphall/Downloads/uBoost_v2/TMVA-v4.1.2/lib/ -lTMVA
#LIBS         = ${ROOT_LIBS} ${BOOST_LIB_OPT}

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

