#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "21" "MagDown" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)]" >logmuonstrip21logdown.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "21" "MagUp" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)]" >logmuonstrip21logup.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "21r1" "MagDown" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)]" >logmuonstrip21r1logdown.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "21r1" "MagUp" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V2ProbNNmu > 0.3)]" >logmuonstrip21r1logup.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "26" "MagDown" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)]" >logmuonstrip26logdown.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "26" "MagUp" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)]" >logmuonstrip26logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "23_MCTuneV1" "MagDown" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)]" >logmuonstrip23MCtune1down.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "23_MCTuneV1" "MagUp" "Mu" "[ (nShared==0), (nShared==0) && (DLLmu > 0.0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3)]" >logmuonstrip23MCtune1logup.txt


