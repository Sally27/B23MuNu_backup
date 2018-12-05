#!/bin/bash

#rm *.root *.pdf


for i in /vols/lhcb/ss4314/preparecontrolweights/preparecontrolweights_FUMSB_simultaneous_NewTCK_PIDoptimisation_extremeweights/*root;

do

./mainLOW $i


done


./main Strip21 MagUp

#./main Strip21 MagDown

#./main Strip21r1 MagUp

#./main Strip21r1 MagDown

