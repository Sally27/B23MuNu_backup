
cd bin

./plotnice "lowFCME"
./plotnice "highFCME"
./plot_individual_effi "lowFCME"
./plot_individual_effi "highFCME"
./plot_ratio_effi "lowFCME"
./plot_ratio_effi "highFCME"
./plot_individual_effi_SBS
./plotnice_SBS

mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_simultaneous_NewTCK_neweffcalc/plot_interesting
cp *pdf /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_simultaneous_NewTCK_neweffcalc/plot_interesting/
