. LbLogin.sh -c x86_64-slc6-gcc48-opt


SetupUrania
make clean

source clean.sh

KFOLD_PATH=/vols/lhcbdisk05/ss4314/usefulfuncs/kfold/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KFOLD_PATH

DEND_PATH=/vols/lhcbdisk05/ss4314/TMVA/dendrology-master/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DEND_PATH

make
