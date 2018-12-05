
SetupProject Urania v5r0

ERR_PATH=/vols/lhcb/ss4314/error_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ERR_PATH

STYLE_PATH=/vols/lhcb/ss4314/style_library/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$STYLE_PATH

DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

mkdir ~/public_html/fitsignal/fitsignal_final_freepar

cut=probnnmu035
cut2=probmu35

make clean
make

cd bin


rm ../FOM/*
rm ../workspace/*
rm ../workspace_fit/*
rm ../workspace_fitcls/*
rm ../workspace_fitfunction/*
rm ../workspace_plots/*
rm ../workspace_preparation/*
rm ../compare_fits/*
rm ../fit_results/*


./main $cut $cut2

cd ../

mkdir ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2
mkdir ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/workspace_preparation

mkdir ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/misid_shapes_nocross_andcross

cp workspace_preparation/*pdf ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/workspace_preparation/ 
cp workspace_preparation/*txt ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/workspace_preparation/
cp misid_shapes_nocross_andcross/*pdf ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/misid_shapes_nocross_andcross/

mkdir ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/workspace_plots

cp workspace_plots/*pdf ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/workspace_plots/
cp workspace_plots/*txt ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/workspace_plots/


mkdir ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/FOM

cp FOM/*txt ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/FOM/

mkdir ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/compare_fits

cp compare_fits/* ~/public_html/fitsignal/fitsignal_final_freepar/$cut$cut2/compare_fits/

    



