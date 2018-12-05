#!/bin/bash

# You need SetupProject Urania v3r0 first!!

#path="/vols/lhcbdisk03/alvarezc/gangadir/workspace/palvare1/LocalXML/"
path="/home/hep/ss4314/gangadir/workspace/ss4314/LocalXML/"
names=("BuKMuMuMC2012_Strip21locally_noKaonPID_noMuonPID_MagUp")
end=".root"

iter=""
subdirs=(286)       #(501 502 505)
subjobs=(237)       #(1635 2954 14)
numbers=(0)       #(0 1 2)


#output="/vols/lhcbdisk03/alvarezc/B2Kee_Kmumu/B2Kee_data/BDT_training/kfold5/"
output="/vols/lhcb/ss4314/final_tuples/mc/norm_mc/2012/MC_B2JpsiK_2012_MagUp.root"


for j in "${numbers[@]}";do
    dir=${subdirs[j]}
    subjob=${subjobs[j]}
    pathj=$path$dir
    name_bef=${names[j]}$end
    for i in `seq 0 ${subjob}`; do
      iter+=$pathj/$i"/output/"$name_bef" "
    done
done


echo
echo "Merged outputfile: "$output
echo 
echo "Merging inputfiles: "$iter
echo
echo "Merging..."
hadd -k -f $output $iter
echo 
