#!/bin/bash

#path=/vols/lhcbdisk05/ss4314/preparetuplesforBDTincludeJpsi/comparedistributions/
#name=variableminq2beforeq2.pdf

path=$1
name=$2

scp ss4314@lx04.hep.ph.ic.ac.uk:$path$name . 
