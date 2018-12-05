#!/bin/bash

#rm *.root *.pdf

VAR1=Strip21
VAR2=MagUp

./main Strip21 MagUp /vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_HighFCME.root HighFCME
./main Strip21 MagUp /vols/lhcb/ss4314/cutonFCME/FUMSB_simultaneous/B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root B23MuNuMCallvar_MCtruth_trigger_Jpsi_qmincut_CombBasic_MisidBasic_FitCorM_LowFCME.root LowFCME

#./main Strip21 MagDown

#./main Strip21r1 MagUp

#./main Strip21r1 MagDown

