KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/beforejack/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

cp /vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_genlevelcor_allsyst_Run1only/workspace_fitcls/*root bin/

cp /vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_genlevelcor_allsyst_Run1only/workspace_fitcls/fitresults_forCLs.root bin/fitresults_forCLs_2.root
cp /vols/lhcb/ss4314/fitsignal/fitsignal_simultaneous_final_genlevelcor_allsyst_Run1only/workspace_fitcls/fitresults_forCLs.root bin/fitresults_forCLs_3.root
