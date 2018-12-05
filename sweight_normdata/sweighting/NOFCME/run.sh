#!bin/bash/

SetupProject Urania v5r0

mkdir ~/public_html/fitcontrol_selection/2012


make clean
make

cd bin


rm ../FOM/*
rm ../workspace/*
rm ../FitResults/*

for i in 0 1 2 3 4 5 6 7;

do

    ./main $i

    mkdir ~/public_html/fitcontrol_selection/2012/selection_$i
    mkdir ~/public_html/fitcontrol_selection/2012/selection_$i/workspace
    
    cp ../workspace/*pdf ~/public_html/fitcontrol_selection/2012/selection_$i/workspace/
    cp ../workspace/*txt ~/public_html/fitcontrol_selection/2012/selection_$i/workspace/
    
    mkdir ~/public_html/fitcontrol_selection/2012/selection_$i/FitResults
    
    cp ../FitResults/*pdf ~/public_html/fitcontrol_selection/2012/selection_$i/FitResults/
    cp ../FitResults/*root ~/public_html/fitcontrol_selection/2012/selection_$i/FitResults/
    cp ../FitResults/*txt ~/public_html/fitcontrol_selection/2012/selection_$i/FitResults/
    
    
    mkdir ~/public_html/fitcontrol_selection/2012/selection_$i/FOM
    
    cp ../FOM/*txt ~/public_html/fitcontrol_selection/2012/selection_$i/FOM/
    

done

