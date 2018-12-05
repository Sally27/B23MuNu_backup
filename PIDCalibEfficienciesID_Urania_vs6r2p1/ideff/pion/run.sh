python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip21logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip21r1logdown.txt

