python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logidkaonstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logidkaonstrip21logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logidkaonstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logidkaonstrip21r1logdown.txt

