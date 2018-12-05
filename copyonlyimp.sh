#!bin/bash/

sourc=$PWD/fitjpsikst/fitjpsikst_idPION_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta/NOFCME
desti=$PWD/calculate_all_preBDT_efficiencies

cp $sourc/* $desti/
cp -r $sourc/src $desti/
cp -r $sourc/include $desti/

mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs
