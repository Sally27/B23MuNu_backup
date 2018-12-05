SetupProject Urania v5r0
KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH
rm workspace/*
#rm info/*

#cd bin
#
#
#for cut in BasicCut probnnmunew probnnmu02 probnnmu025 probnnmu03 probnnmu035 probnnmupi04 probnnmupi05
#do  
#
#    ./mainRun1 $cut
#    
#done
#
#for i in *.tex; do pdflatex $i;done
#
#cd ../
#
#mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_simultaneous_final_optimisation_GenLevelEff
#
#cp bin/*.tex /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_simultaneous_final_optimisation_GenLevelEff/
#cp bin/*.pdf /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_simultaneous_final_optimisation_GenLevelEff/


cd bin

#for cut2 in probmu35
for cut2 in BasicCut probmu1 probmu15 probmu2 probmu25 probmu3 probmu35



do

    ./main2016 $cut2

done

for i in *.tex; do pdflatex $i;done

cd ../

cp bin/*.tex /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_simultaneous_final_optimisation_GenLevelEff/
cp bin/*.pdf /home/hep/ss4314/public_html/SingelEventSensitivity/fitsignal_simultaneous_final_optimisation_GenLevelEff/

