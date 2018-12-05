
SetupProject Urania v5r0


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

mkdir ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded

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

mkdir ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2
mkdir ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/workspace_preparation

cp workspace_preparation/*pdf ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/workspace_preparation/ 
cp workspace_preparation/*txt ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/workspace_preparation/

mkdir ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/workspace_plots

cp workspace_plots/*pdf ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/workspace_plots/
cp workspace_plots/*txt ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/workspace_plots/


mkdir ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/FOM

cp FOM/*txt ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/FOM/

mkdir ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/compare_fits

cp compare_fits/* ~/public_html/fitsignal/fitsignal_final_GenLevelEff_CorrectMisid_niceplotsincluded/$cut$cut2/compare_fits/

    



