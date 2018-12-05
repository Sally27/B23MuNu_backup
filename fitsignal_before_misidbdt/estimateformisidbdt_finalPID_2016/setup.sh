
KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

STYLE_PATH=/vols/lhcb/ss4314/style_library_2/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$STYLE_PATH

rm FOM/*
rm workspace/*
rm workspace_fit/*
rm workspace_fitcls/*
rm workspace_fitfunction/*
rm workspace_plots/*
rm workspace_preparation/*
rm misid_shapes_nocross_andcross/*
