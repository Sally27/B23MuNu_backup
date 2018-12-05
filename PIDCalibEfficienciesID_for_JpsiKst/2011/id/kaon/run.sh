python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "K" "[DLLK > 0.0 && IsMuon==0.0 && (DLLK-DLLp) > 0.0]" > logidkaonstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "K" "[DLLK > 0.0 && IsMuon==0.0 && (DLLK-DLLp) > 0.0]" > logidkaonstrip21r1logdown.txt

