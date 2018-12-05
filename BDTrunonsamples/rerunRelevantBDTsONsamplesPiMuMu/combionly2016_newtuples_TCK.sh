#!/bin/bash
#. LbLogin.sh -c x86_64-slc6-gcc46-opt


cd ../

. SetupProject.sh Urania v5r0 #v2r0p1

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



VAR1=/vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/pimumu_mc/2016/bin/MC_B2PiMuMu_2016_L0MuonDecisionTOS_trigger_Jpsi.root
VAR2=/vols/lhcb/ss4314/final_tuples_analyser/data/sig_data/2016/FullUpperMassSideBand/bin/Bu23MuNuData2016_corrmFUSMB_trigger_Jpsi_mu1isMuonTight_mu2isMuonTight_mu3isMuonTight_mu1MuonNShared_mu2MuonNShared_mu3MuonNShared_qmincut.root
 

VAR4=10


weight=W

#read -p "SPECIFY NAME OF THE TRAINING? " -e trainingname
#echo Your trainingname is $trainingname
#echo Your trainingname is $trainingname > /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
#
#read -p "SPECIFY TAG you want to use to apply BDT/ could be also TRAINING NAME? " -e tag
#echo Your TAG is $tag
#echo Your TAG is $tag >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt
#
#read -p "SPECIFY THE NAME OF THE BDT BRANCH in TRAINING? " -e bdt
#echo Your BDTBranch is $bdt
#echo Your BDTBranch is $bdt >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

trainingname=MCSig2016_288888335_vs_DATACombi2016
namediff=_ONLY_PiMuMu
tag=$trainingname$namediff
bdt=MCSig2016_288888335_vs_DATACombi2016NTrees60_MinNodeSize2_MaxDepth3_SeparationTypeGiniIndex_PruneMethodNoPruning_DoPreselection

echo Your trainingname is $trainingname
echo Your trainingname is $trainingname > /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

echo Your TAG is $tag
echo Your TAG is $tag >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

echo Your BDTBranch is $bdt
echo Your BDTBranch is $bdt >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt


dktree=DecayTree


echo "Changing directory to BDTtrainings to get the training"

cd /vols/lhcb/ss4314/BDTtrainings/$trainingname

echo "Copying weights to bin directory"

cp -rf weights/ /vols/lhcb/ss4314/BDTrunonsamples/bin/

echo "Copying root files bin directory"

cp -rf tmva/ /vols/lhcb/ss4314/BDTrunonsamples/bin/


echo "Running on usual files"


echo "Your files run on are:/vols/lhcb/ss4314/final_tuples_analyser/mc/sig_mc_PHSP/2012/bin/B23MuNuMCPHSP_MCtruth_L0MuonDecisionTOS_trigger_Jpsi.root"  >> /vols/lhcb/ss4314/BDTrunonsamples/summaryrun.txt

for runfile in /vols/lhcb/ss4314/final_tuples_analyser_PO_AND_UE/mc/pimumu_mc/2016/bin/MC_B2PiMuMu_2016_L0MuonDecisionTOS_trigger_Jpsi.root  

do

	echo "This is runfile"

	echo $runfile


	echo "Copying the runfile into dataset directory"

	cp $runfile /vols/lhcb/ss4314/BDTrunonsamples/datasets/

done

for myfile in MC_B2PiMuMu_2016_L0MuonDecisionTOS_trigger_Jpsi.root

do

	newrunfileloc=/vols/lhcb/ss4314/BDTrunonsamples/datasets/$myfile

	cd /vols/lhcb/ss4314/BDTrunonsamples/bin/


	file="./kfoldbacknomu1mu3"
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
