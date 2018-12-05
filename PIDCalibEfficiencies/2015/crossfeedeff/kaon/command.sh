#!/bin/sh

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "23_MCTuneV1" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip23logup.txt

echo "done1"

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "23_MCTuneV1" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip23logdown.txt

echo "done2"

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "26" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip26logup.txt


echo "done3"


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "26" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidkaonstrip26logdown.txt


echo "done4"
