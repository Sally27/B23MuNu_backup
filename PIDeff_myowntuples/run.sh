#!/bin/bash

cd bin

#var1=PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016

#var2=PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2016

./main_kaon_2016 PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2016 
./main_pion_2016 PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2016
./main_kaon_run1 PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2011
./main_pion_run1 PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2011
./main_kaon_run1 PID_2D_ALL_INFO_FORANALYSIS_KAONMISID_2012
./main_pion_run1 PID_2D_ALL_INFO_FORANALYSIS_PIONMISID_2012

cp *ALT* ../PIDrebinnedtuples/
