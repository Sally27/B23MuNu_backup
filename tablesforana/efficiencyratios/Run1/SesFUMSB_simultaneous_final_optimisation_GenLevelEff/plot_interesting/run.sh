
cd bin

./plotnice "lowFCME" "probnnmu035" "probmu35"
./plotnice "highFCME" "probnnmu035" "probmu35"
./plot_individual_effi "lowFCME" "probnnmu035" "probmu35"
./plot_individual_effi "highFCME" "probnnmu035" "probmu35"
./plot_ratio_effi "lowFCME" "probnnmu035" "probmu35"
./plot_ratio_effi "highFCME" "probnnmu035" "probmu35"
./plot_individual_effi_SBS "probnnmu035" "probmu35"
./plot_individual_effi_SBS_ratio "probnnmu035" "probmu35"
#./plotnice_SBS

#mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_simultaneous_NewTCK_neweffcalc/plot_interesting
#cp *pdf /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_simultaneous_NewTCK_neweffcalc/plot_interesting/
