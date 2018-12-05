#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagUp" "K" "[Brunel_DLLK > 0.0 && Brunel_IsMuon==0.0 && (Brunel_DLLK-Brunel_DLLp) > 0.0]" > logidkaonstripTurbo16logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagDown" "K" "[Brunel_DLLK > 0.0 && Brunel_IsMuon==0.0 && (Brunel_DLLK-Brunel_DLLp) > 0.0]" > logidkaonstripTurbo16logdown.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16r1" "MagUp" "K" "[Brunel_IsMuon==0.0 && InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstripTurbo16r1logup.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16r1" "MagDown" "K" "[Brunel_IsMuon==0.0 && InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstripTurbo16r1logdown.txt

