ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH

STYLE_PATH=/vols/lhcb/ss4314/style_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$STYLE_PATH

DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH



KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH



rm FOM/*
rm workspace/*
rm workspace_fit/*
rm workspace_fitcls/*
rm workspace_fitfunction/*
rm workspace_plots/*
rm workspace_preparation/*
rm compare_fits/*
rm fit_results/*
