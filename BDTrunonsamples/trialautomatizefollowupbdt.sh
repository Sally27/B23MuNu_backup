#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania #v2r0p1

#export TMVALOC=/vols/lhcbdisk05/ss4314/TMVA/kfoldandubdt/optimizedubdt/uboost/TMVA-v4.1.2
#export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
#echo "$TMVALOC"
DEND_PATH=/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

make clean

echo "Do you wish to change input variables or options for BDT?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cd src/; echo "Do your changes and run this script again selecting no";  return;;
        No ) make; break;;
    esac
done


VAR1=/vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root
VAR2=/vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb.root
 

VAR4=10


weight=W

read -p "SPECIFY NAME FOR THIS TRAINING? " -e trainingname
echo Your trainingname is $trainingname
echo Your trainingname is $trainingname > /vols/lhcbdisk05/ss4314/BDTrunonsamples/summaryrun.txt

read -p "SPECIFY TAG could be also TRAINING NAME? " -e tag
echo Your TAG is $tag
echo Your TAG is $tag >> /vols/lhcbdisk05/ss4314/BDTrunonsamples/summaryrun.txt

read -p "SPECIFY THE NAME OF THE BDT BRANCH? " -e bdt
echo Your TAG is $bdt
echo Your TAG is $bdt >> /vols/lhcbdisk05/ss4314/BDTrunonsamples/summaryrun.txt



dktree=DecayTree


echo "Changing directory to BDTtrainings to get the training"

cd /vols/lhcbdisk05/ss4314/BDTtrainings/$trainingname

echo "Copying weights to bin directory"

cp -rf weights/ /vols/lhcbdisk05/ss4314/BDTrunonsamples/bin/

echo "Copying_60TreesComb.root files bin directory"

cp -rf tmva/ /vols/lhcbdisk05/ss4314/BDTrunonsamples/bin/


echo "Running on usual files"

echo "Your files run on are: /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/B23Pimu_MCtruth_Jpsi_cut_mu3nShared_qmincut_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root "  >> /vols/lhcbdisk05/ss4314/BDTrunonsamples/summaryrun.txt

for runfile in  /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/B23Pimu_MCtruth_Jpsi_cut_mu3nShared_qmincut_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb.root /vols/lhcbdisk05/ss4314/cutonBDTs/allvarcombvsmcsigCOMB/B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root


do

	echo "This is runfile"

	echo $runfile


	echo "Copying the runfile into dataset directory"

	cp $runfile /vols/lhcbdisk05/ss4314/BDTrunonsamples/datasets/

done

for myfile in Data2012and2011_corrm_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_60TreesComb.root B23Pimu_MCtruth_Jpsi_cut_mu3nShared_qmincut_60TreesComb.root SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_60TreesComb.root SSMisIDsmalldatasample_mu3isNotMuon_mu3inMuonAcc_Jpsi_cut_mu1nShared_mu2nShared_qmincut_60TreesComb.root B23MuNuMCallvar_MCtruth_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_60TreesComb.root

do

	newrunfileloc=/vols/lhcbdisk05/ss4314/BDTrunonsamples/datasets/$myfile

	cd /vols/lhcbdisk05/ss4314/BDTrunonsamples/bin/


	file="./kfoldincludeP"
        echo "the option is $file" >> /vols/lhcbdisk05/ss4314/BDTrunonsamples/summaryrun.txt
	if [ -e $file ]; then
		echo "File exists"
		$file -s $VAR1 -b $VAR2 -k $VAR4 --sig-tree $dktree --bkg-tree $dktree  -w $weight  --bdt $bdt  -r $newrunfileloc


	else 
		echo "File does not exits, I will not do anything. Just saying..."

	fi

	echo "Coppying trained and applied BDT"

	mkdir /vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag

	cp $newrunfileloc /vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
       
done


echo "put all training into /vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag"
echo "put all training into /vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag" >> /vols/lhcbdisk05/ss4314/BDTrunonsamples/summaryrun.txt
cp  /vols/lhcbdisk05/ss4314/BDTrunonsamples/summaryrun.txt  /vols/lhcbdisk05/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
 
echo "FINISHED"
