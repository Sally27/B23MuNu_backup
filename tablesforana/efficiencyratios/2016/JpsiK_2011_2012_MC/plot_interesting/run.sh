cd bin

./plot_individual_effi "probnnmu035" "probmu35" 
./plot_individual_effi_SBS "probnnmu035" "probmu35" 
./plot_individual_effi_SBS_percent "probnnmu035" "probmu35" 
./plotnice "probnnmu035" "probmu35"
./plot_ratio_effi "probnnmu035" "probmu35"
./plot_ratio_effi_pretty "probnnmu035" "probmu35"
./makeimptable "probnnmu035" "probmu35"
#mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/plot_interesting
#cp *pdf /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_NewTCK_neweffcalc/plot_interesting/
