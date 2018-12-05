#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania #v2r0p1

#export TMVALOC=/vols/lhcb/ss4314/TMVA/kfoldandubdt/optimizedubdt/uboost/TMVA-v4.1.2
#export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
#echo "$TMVALOC"
DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

make clean

echo "Do you wish to change input variables or options for BDT?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) cd src/; echo "Do your changes and run this script again selecting no";  return;;
        No ) make; break;;
    esac
done


VAR1=/vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuMCallvar_MCtruth_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root
VAR2=/vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_CombBasic.root
 

VAR4=10


weight=W

read -p "SPECIFY NAME FOR THIS TRAINING? " -e trainingname
echo Your trainingname is $trainingname
echo Your trainingname is $trainingname > /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

read -p "SPECIFY TAG could be also TRAINING NAME? " -e tag
echo Your TAG is $tag
echo Your TAG is $tag >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

read -p "SPECIFY THE NAME OF THE BDT BRANCH? " -e bdt
echo Your TAG is $bdt
echo Your TAG is $bdt >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt



dktree=DecayTree


echo "Changing directory to BDTtrainings to get the training"

cd /vols/lhcb/ss4314/BDTtrainings/$trainingname

echo "Copying weights to bin directory"

cp -rf weights/ /vols/lhcb/ss4314/BDTrunonsamples/bin/

echo "Copying files to bin directory"

cp -rf tmva/ /vols/lhcb/ss4314/BDTrunonsamples/bin/


echo "Running on usual files"

echo "Your files run on are: /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/Data2012and2011_corrm_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23Pimu_MCtruth_cut_trigger_Jpsi_cut_mu3nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuMCallvar_MCtruth_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root "  >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

for runfile in  /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/Data2012and2011_corrm_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23Pimu_MCtruth_cut_trigger_Jpsi_cut_mu3nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuMCallvar_MCtruth_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root /vols/lhcb/ss4314/cutonBDTs/allvartriggernoass/B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic.root

do

	echo "This is runfile"

	echo $runfile


	echo "Copying the runfile into dataset directory"

	cp $runfile /vols/lhcb/ss4314/BDTrunonsamples/datasets/

done

for myfile in Data2012and2011_corrm_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_KaonPID_CombBasic.root B23Pimu_MCtruth_cut_trigger_Jpsi_cut_mu3nShared_qmincut_CombBasic.root B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_PionPID_CombBasic.root B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_CombBasic.root B23MuNuMCallvar_MCtruth_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_mu3nShared_qmincut_CombBasic.root B23MuNuFakeSS_mu3isNotMuon_mu3inMuonAcc_cut_trigger_Jpsi_cut_mu1nShared_mu2nShared_qmincut_ProtonPID_CombBasic.root

do

	newrunfileloc=/vols/lhcb/ss4314/BDTrunonsamples/datasets/$myfile

	cd /vols/lhcb/ss4314/BDTrunonsamples/bin/


	file="./kfoldnoassy"
        echo "the option is $file" >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
	if [ -e $file ]; then
		echo "File exists"
		$file -s $VAR1 -b $VAR2 -k $VAR4 --sig-tree $dktree --bkg-tree $dktree  -w $weight  --bdt $bdt  -r $newrunfileloc


	else 
		echo "File does not exits, I will not do anything. Just saying..."

	fi

	echo "Coppying trained and applied BDT"

	mkdir /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag

	cp $newrunfileloc /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
       
done


echo "put all training into /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag"
echo "put all training into /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag" >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
cp  /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt  /vols/lhcb/ss4314/BDTrunonsamples/tuplesandbdtrun/$tag
 
echo "FINISHED"
