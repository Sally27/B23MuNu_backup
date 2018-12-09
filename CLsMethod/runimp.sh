

#path1=/vols/lhcb/ss4314/CLsMethod/expected_limit_sim_allsyst_upgrade_unblinding_allsyst_allsyst/
#tag1=expected_limit_sim_allsyst_upgrade_unblinding_allsyst_allsyst

KFOLD_PATH=/vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/beforejack/docs/customclass/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH


path1=/vols/lhcb/ss4314/CLsMethod/expected_limit_NOTsim_allsyst_upgrade_unblinding/
tag1=expected_limit_NOTsim_allsyst_upgrade_unblinding


cd $path1

source movetoplot.sh

cd plotExclusionLimit/bin

./main


cd ../../

mkdir ~/public_html/CLsmethod/$tag1
mkdir ~/public_html/CLsmethod/$tag1/expected_exclusion
mkdir ~/public_html/CLsmethod/$tag1/smoothing

cp bin/*pdf ~/public_html/CLsmethod/$tag1/expected_exclusion/
cp bin/*txt ~/public_html/CLsmethod/$tag1/expected_exclusion/
cp -r toy_* ~/public_html/CLsmethod/$tag1/expected_exclusion/
cp -r plotExclusionLimit/bin/*pdf ~/public_html/CLsmethod/$tag1/expected_exclusion/
cp -r calculatesmooth/* ~/public_html/CLsmethod/$tag1/smoothing/



