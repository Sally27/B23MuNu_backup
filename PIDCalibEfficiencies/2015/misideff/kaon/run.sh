 python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "23_MCTuneV1" "MagDown" "K" "[(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" >logkaonstrip23logdown.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "23_MCTuneV1" "MagUp" "K" "[(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" > logkaonstrip23logup.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "26" "MagUp" "K" "[(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" > logkaonstrip26logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "26" "MagDown" "K" "[(IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) && ((DLLmu - DLLK) > 0.0) && (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) && (DLLmu > 0.0) && ((DLLmu - DLLK) > 0.0) && (nShared==0) && (V1ProbNNmu > 0.35)]" > logkaonstrip26logdown.txt



