#!/bin/bash
# My first script

. LbLogin.sh -c x86_64-slc6-gcc46-opt
. SetupProject.sh Urania v2r0p1
export TMVALOC=/vols/lhcbdisk05/ss4314/uBoostatt/TMVA-v4.1.2
export LD_LIBRARY_PATH=$TMVALOC/lib/:$LD_LIBRARY_PATH
echo "$TMVALOC"
