SetupProject Urania v5r0
KFOLD_PATH=/vols/lhcb/ss4314/customlib/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

rm  workspace/*

cd bin


#for cut in BasicCut probnnmunew probnnmu02 probnnmu025 probnnmu03 probnnmu035 probnnmupi04 probnnmupi05 probnnmupi06
#do
#
#    ./main $cut
#
#    cd ../
#    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights
#    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/$cut
#    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/NOFCME
#    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/FOM
#    cp workspace/*pdf ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/NOFCME/
#    cp workspace/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/NOFCME/
#    cp FOM/*txt ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/$cut/FOM/
#    rm  workspace/*
#    cd bin
#done

for cut2 in BasicCut probmu1 probmu15 probmu2 probmu25 probmu3 probmu35


do

    ./main2 $cut2

    cd ../
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/NOFCME
    mkdir ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/FOM
    cp workspace/*pdf ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/NOFCME/
    cp workspace/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/NOFCME/
    cp FOM/*txt ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/FOM/
    cp FOM/*root ~/public_html/fitcontrol/fitcontrolchannelFUMSB_NOTsimultaneous_NewTCK_PIDoptimisation_extremeweights/2016_$cut2/FOM/
    rm  workspace/*
    cd bin
done
