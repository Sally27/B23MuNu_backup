# python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "23_MCTuneV1" "MagDown" "Mu" "[(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" >logmuonstrip23logdown.txt


#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "23_MCTuneV1" "MagUp" "Mu" "[(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" > logmuonstrip23logup.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "26" "MagUp" "Mu" "[(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" > logmuonstrip26logup.txt

#python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "IsMuon==1.0" -Z ""  "26" "MagDown" "Mu" "[(DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" > logmuonstrip26logdown.txt



