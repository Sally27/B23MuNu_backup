python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagUp" "P" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLp > 5.0 && ((Brunel_DLLp - Brunel_DLLK) > 5.0)]" > logidprotonstrip23logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo15" "MagDown" "P" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLp > 5.0 && ((Brunel_DLLp - Brunel_DLLK) > 5.0)]" > logidprotonstrip23logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagUp" "P" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLp > 5.0 && ((Brunel_DLLp - Brunel_DLLK) > 5.0)]" > logidprotonstripTurbo16logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "Turbo16" "MagDown" "P" "[Brunel_IsMuon==0.0 && Brunel_InMuonAcc==1.0 && Brunel_DLLp > 5.0 && ((Brunel_DLLp - Brunel_DLLK) > 5.0)]" > logidprotonstripTurbo16logdown.txt

