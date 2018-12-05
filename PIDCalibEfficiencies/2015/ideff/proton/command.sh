#!/bin/bash

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logidprotonstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logidprotonstrip21logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logidprotonstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logidprotonstrip21r1logdown.txt

