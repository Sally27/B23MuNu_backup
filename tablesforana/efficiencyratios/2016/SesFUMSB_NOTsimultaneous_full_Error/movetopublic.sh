#!/bin/bash

mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error

mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/calculation
plot_interesting/bin/

cp bin/*.tex /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/calculation/
cp bin/*.pdf /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/calculation/

echo $PWD >> pathtocode.txt

cp pathtocode.txt /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/

mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/plots_and_tables

cp plot_interesting/bin/*tex /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/plots_and_tables/
cp plot_interesting/bin/*pdf /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/plots_and_tables/

mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_calculation

cp -r include /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_calculation/
cp -r src /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_calculation/

cp Makefile /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_calculation/
cp *sh /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_calculation/


mkdir /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_plots_and_tables

cp -r plot_interesting/include /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_plots_and_tables/
cp -r plot_interesting/src /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_plots_and_tables/

cp plot_interesting/Makefile /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_plots_and_tables/
cp plot_interesting/*sh /home/hep/ss4314/public_html/SingelEventSensitivity/SesFUMSB_NOTsimultaneous_full_Error/code_plots_and_tables/

