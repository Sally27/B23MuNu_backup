
SetupProject Urania v5r0


KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

mkdir ~/public_html/fitsignal/fitsignal_final_optimisation


#for cut in BasicCut probnnmunew probnnmu02 probnnmu025 probnnmu03 probnnmu035 probnnmupi04 probnnmupi05
#do
#    make clean
#    make
#
#    cd bin
#    
#    
#    rm ../FOM/*
#    rm ../workspace/*
#    rm ../workspace_fit/*
#    rm ../workspace_fitcls/*
#    rm ../workspace_fitfunction/*
#    rm ../workspace_plots/*
#    rm ../workspace_preparation/*
#    rm ../compare_fits/*
#    rm ../fit_results/*
#   
#
#    ./main $cut 2012
# 
#    cd ../
#    
#    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/$cut
#    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/workspace_preparation
#    
#    cp workspace_preparation/*pdf ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/workspace_preparation/ 
#    cp workspace_preparation/*txt ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/workspace_preparation/
#    
#    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/workspace_plots
#    
#    cp workspace_plots/*pdf ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/workspace_plots/
#    cp workspace_plots/*txt ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/workspace_plots/
#    
#    
#    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/FOM
#    
#    cp FOM/*txt ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/FOM/
#    
#    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/compare_fits
#    
#    cp compare_fits/* ~/public_html/fitsignal/fitsignal_final_optimisation/$cut/compare_fits/
#
#    
#
#done

for cut2 in BasicCut #probmu1 probmu15 probmu2 probmu25 probmu3 probmu35


do
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
   

    ./main $cut2 2016
 
    cd ../
    
    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2
    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/workspace_preparation
    
    cp workspace_preparation/*pdf ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/workspace_preparation/ 
    cp workspace_preparation/*txt ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/workspace_preparation/
    
    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/workspace_plots
    
    cp workspace_plots/*pdf ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/workspace_plots/
    cp workspace_plots/*txt ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/workspace_plots/
    
    
    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/FOM
    
    cp FOM/*txt ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/FOM/
    
    mkdir ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/compare_fits
    
    cp compare_fits/* ~/public_html/fitsignal/fitsignal_final_optimisation/2016_$cut2/compare_fits/

    

done
