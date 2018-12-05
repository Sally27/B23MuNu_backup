#!/bin/bash

#rm *.root *.pdf


./mainLOW
./mainHIGH
./maincut

source hadd_opt.sh
