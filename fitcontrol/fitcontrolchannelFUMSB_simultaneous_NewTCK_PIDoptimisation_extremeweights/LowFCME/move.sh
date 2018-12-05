SetupProject Urania v5r0
KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

rm  workspace/*

cd bin

for cut in BasicCut probnnmunew probnnmu02 probnnmu025 probnnmu03 probnnmu035 probnnmupi04 probnnmupi05 #probnnmupi06
do

    ./main $cut LowFCME

    cd ../
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/LowFCME
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/LowFCME/FOM
    cp workspace/*pdf ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/LowFCME/
    cp workspace/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/LowFCME/
    cp FOM/*txt ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/LowFCME/FOM/
    cp FOM/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/LowFCME/FOM/
    rm  workspace/*
    rm  FOM/*
    cd bin
done

for cut in BasicCut probnnmunew probnnmu02 probnnmu025 probnnmu03 probnnmu035 probnnmupi04 probnnmupi05 #probnnmupi06
do

    ./main $cut HighFCME

    cd ../
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/HighFCME
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/HighFCME/FOM
    cp workspace/*pdf ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/HighFCME/
    cp workspace/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/HighFCME/
    cp FOM/*txt ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/HighFCME/FOM/
    cp FOM/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/HighFCME/FOM/
    rm  workspace/*
    rm  FOM/*
    cd bin
done
for cut2 in BasicCut probmu1 probmu15 probmu2 probmu25 probmu3 probmu35


do

    ./main2 $cut2 LowFCME

    cd ../
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/LowFCME
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/LowFCME/FOM
    cp workspace/*pdf ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/LowFCME/
    cp workspace/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/LowFCME/
    cp FOM/*txt ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/LowFCME/FOM/
    cp FOM/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/LowFCME/FOM/
    rm  workspace/*
    rm  FOM/*
    cd bin
done


for cut2 in BasicCut probmu1 probmu15 probmu2 probmu25 probmu3 probmu35
do

    ./main2 $cut2 HighFCME

    cd ../
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/HighFCME
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/HighFCME/FOM
    cp workspace/*pdf ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/HighFCME/
    cp workspace/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/HighFCME/
    cp FOM/*txt ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/HighFCME/FOM/
    cp FOM/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/HighFCME/FOM/
    rm  workspace/*
    rm  FOM/*
    cd bin
done






