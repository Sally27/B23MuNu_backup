. LbLogin.sh -c x86_64-slc6-gcc49-opt


SetupUrania v4r0
make clean


KFOLD_PATH=/vols/lhcb/ss4314/usefulfuncs/kfold/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

DEND_PATH=/vols/lhcb/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

make
