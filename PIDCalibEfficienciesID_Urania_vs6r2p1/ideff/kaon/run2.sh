#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagUp" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstrip23logup.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagDown" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstrip23logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagUp" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstripTurbo16logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagDown" "K" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLK > 0.0 && ((Brunel_DLLp - Brunel_DLLK) < 5.0)]" > logidkaonstripTurbo16logdown.txt

