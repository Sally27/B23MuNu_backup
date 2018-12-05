#!bin/bash/

sourc=$PWD/fitjpsikst_idKAON_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta_2016/NOFCME
desti=$PWD/fitjpsikst_idKAON_includeswaps_automatize_master_sweight_cinMuonAc_NOghostprob_mydefbin_onnlyONEbinINeta_2016_newPIDopt/NOFCME

mkdir $desti

cp $sourc/* $desti/
mkdir $desti/src

cp $sourc/src/* $desti/src/
cp -r $sourc/include $desti/

mkdir $desti/bin
cp $sourc/bin/*sh $desti/bin/

mkdir $desti/obj
mkdir $desti/docs
