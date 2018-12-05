python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "23_MCTuneV1" "MagUp" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip23logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "23_MCTuneV1" "MagDown" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip23logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "26" "MagUp" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip26logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "26" "MagDown" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logidpionstrip26logdown.txt

