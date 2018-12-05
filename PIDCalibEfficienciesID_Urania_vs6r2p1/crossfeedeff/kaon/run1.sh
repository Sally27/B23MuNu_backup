#!/bin/sh

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip21logup.txt

echo "done1"

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip21logdown.txt

echo "done2"

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip21r1logup.txt


echo "done3"


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip21r1logdown.txt


echo "done4"
