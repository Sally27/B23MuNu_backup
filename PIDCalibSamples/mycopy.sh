#!/bin/bash


for x in {0..71};
do echo $x;
xrdcp root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb/calib/lhcb/calib/pid/CalibData//Reco14_DATA/MagDown/DSt_Pi_MagDown_Strip20_$x.root . ;
done;
