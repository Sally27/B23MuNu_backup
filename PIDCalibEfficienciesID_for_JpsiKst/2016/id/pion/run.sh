python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagUp" "Pi" "[Brunel_DLLK < 0.0 && Brunel_IsMuon==0.0 && Brunel_DLLp < 0.0]" > logidpionstripTurbo16logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagDown" "Pi" "[Brunel_DLLK < 0.0 && Brunel_IsMuon==0.0 && Brunel_DLLp < 0.0]" > logidpionstripTurbo16logdown.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16r1" "MagUp" "K" "[Brunel_IsMuon==0.0 && InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstripTurbo16r1logup.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16r1" "MagDown" "K" "[Brunel_IsMuon==0.0 && InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstripTurbo16r1logdown.txt

