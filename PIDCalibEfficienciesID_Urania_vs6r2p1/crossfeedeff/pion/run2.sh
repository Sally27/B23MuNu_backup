#!/bin/sh

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagUp" "Pi" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidpionstrip23logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagDown" "Pi" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidpionstrip23logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagUp" "Pi" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidpionstripTurbo16logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagDown" "Pi" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidpionstripTurbo16logdown.txt

