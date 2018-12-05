
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

cd bin

./plot_individual_effi "probnnmu035" "probmu35" 
./plot_individual_effi_pretty "probnnmu035" "probmu35" 
./plot_individual_effi_SBS "probnnmu035" "probmu35" 
./plot_individual_effi_SBS_percent "probnnmu035" "probmu35" 
./plotnice "probnnmu035" "probmu35"
./plot_ratio_effi "probnnmu035" "probmu35"
./plot_ratio_effi_pretty "probnnmu035" "probmu35"
./makeimptable "probnnmu035" "probmu35"
#mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/plot_interesting
#cp *pdf /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/plot_interesting/
