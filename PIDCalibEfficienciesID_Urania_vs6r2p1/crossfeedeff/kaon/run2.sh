#!/bin/sh

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagUp" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK < 0.0 && Brunel_DLLp < 5.0]" > logidkaonstrip23logup.txt

echo "done1"

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagDown" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK < 0.0 && Brunel_DLLp < 5.0]" > logidkaonstrip23logdown.txt

echo "done2"

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagUp" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK < 0.0 && Brunel_DLLp < 5.0]" > logidkaonstripTurbo16logup.txt


echo "done3"


#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagDown" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK < 0.0 && Brunel_DLLp < 5.0]" > logidkaonstripTurbo16logdown.txt


#echo "done4"
