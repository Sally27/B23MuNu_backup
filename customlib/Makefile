INCLUDE=-I/vols/lhcb/ss4314/customlib/include
INCLUDEDIR=/vols/lhcb/ss4314/customlib/include
ROOTLIBS = `root-config --cflags --libs` -lMinuit -lFoam -lRooFit -lRooFitCore -lMathMore
LIBDIR = /vols/lhcb/ss4314/customlib/lib
CC =g++
SHARED = $(CC) -shared -o
all : lib/libcustomroofit.so

lib/libcustomroofit.so : src/MyCB.cpp src/RooHypathia.cpp src/RooIpatia2.cpp $(INCLUDEDIR)/MyCB.hpp $(INCLUDEDIR)/RooHypathia.hpp $(INCLUDEDIR)/RooIpatia2.hpp
	@rootcint -f  /vols/lhcb/ss4314/customlib/lib/eventdict.cc -c -I/$(INCLUDEDIR) MyCB.hpp RooHypathia.hpp RooIpatia2.hpp
	$(CC) -fPIC -shared -o $(LIBDIR)/libcustomroofit.so $(INCLUDE) lib/eventdict.cc src/MyCB.cpp src/RooHypathia.cpp src/RooIpatia2.cpp $(ROOTLIBS) -L$(LIBDIR)

#lib/libcustomroofit.so : src/RooHypathia.cpp $(INCLUDEDIR)/RooHypathia.hpp
#	@rootcint -f  /vols/lhcb/ss4314/customlib/lib/eventdict.cc -c -I/$(INCLUDEDIR) RooHypathia.hpp 
#	$(CC) -fPIC -shared -o $(LIBDIR)/libcustomroofit.so $(INCLUDE) lib/eventdict.cc src/RooHypathia.cpp $(ROOTLIBS) -L$(LIBDIR)

.PHONY : clean

clean :
	rm -f obj/* bin/* lib/*

