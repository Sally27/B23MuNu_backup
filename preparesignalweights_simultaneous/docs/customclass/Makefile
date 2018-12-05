INCLUDE=-I/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/include
INCLUDEDIR=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/include
ROOTLIBS = `root-config --cflags --libs` -lMinuit -lFoam -lRooFit -lRooFitCore -lMathMore
LIBDIR = /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
CC =g++
SHARED = $(CC) -shared -o
all : lib/libcustomroofit.so

lib/libcustomroofit.so : src/MyCB.cpp $(INCLUDEDIR)/MyCB.hpp
	@rootcint -f  /vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib/eventdict.cc -c -I/$(INCLUDEDIR) MyCB.hpp 
	$(CC) -fPIC -shared -o $(LIBDIR)/libcustomroofit.so $(INCLUDE) lib/eventdict.cc src/MyCB.cpp $(ROOTLIBS) -L$(LIBDIR)

.PHONY : clean

clean :
	rm -f obj/* bin/* lib/*

