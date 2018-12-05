SetupProject Urania v5r0


ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH
 
STYLE_PATH=/vols/lhcb/ss4314/style_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$STYLE_PATH

ROOF_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOF_PATH

KFOLD_PATH=/vols/lhcb/ss4314/adapttbcode/kfold/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH


rm workspace/*
#rm info/*
make

cd bin


#for cut in probnnmu035 probmu35 
#do  
./mainMC_cutnspd450 probnnmu035 probmu35
./mainMC probnnmu035 probmu35
./mainData  
#done

for i in *.tex; do pdflatex $i;done

#cd ../
#
#mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_final_optimisation_GenLevelEff
#
#cp bin/*.tex /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_final_optimisation_GenLevelEff/
#cp bin/*.pdf /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_final_optimisation_GenLevelEff/


#cd bin
#
#for cut2 in probmu35
#
#
#
#do
#
#    ./main2016 $cut2
#
#done
#
#for i in *.tex; do pdflatex $i;done
#

