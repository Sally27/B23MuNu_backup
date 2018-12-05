python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "23_MCTuneV1" "MagDown" "Pi" "[(IsMuon==1.0),  (IsMuon==1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) &&  (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) &&  (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.35)]" > logpionstrip23logdown.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "23_MCTuneV1" "MagUp" "Pi" "[(IsMuon==1.0),  (IsMuon==1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) &&  (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) &&  (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.35)]" > logpionstrip23logup.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "26" "MagUp" "Pi" "[(IsMuon==1.0),  (IsMuon==1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) &&  (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) &&  (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.35)]" > logpionstrip26logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "26" "MagDown" "Pi" "[(IsMuon==1.0),  (IsMuon==1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) &&  (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) &&  (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.6), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.5), (IsMuon==1.0) &&  (nShared==0) && ((V1ProbNNmu - V1ProbNNpi) > -0.4), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.2), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.25), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.3), (IsMuon==1.0) &&  (nShared==0) && (V1ProbNNmu > 0.35)]" > logpionstrip26logdown.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "21" "MagUp" "Pi" "[(IsMuon==1.0),  (IsMuon==1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) &&  (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) &&  (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) &&  (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6), (IsMuon==1.0) &&  (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5), (IsMuon==1.0) &&  (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.2), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.25), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.3), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.35)]" > logpionstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Unbias_HLT1==1.0" -Z ""  "21" "MagDown" "Pi" "[(IsMuon==1.0),  (IsMuon==1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 0.5) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.0) &&  (nShared==0), (IsMuon==1.0) && (DLLmu > 1.5) &&  (nShared==0),  (IsMuon==1.0) && (DLLmu > 2.0) &&  (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 0.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.0) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 1.5) && (nShared==0), (IsMuon==1.0) && ((DLLmu - DLLK) > 2.0) && (nShared==0), (IsMuon==1.0) &&  (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.6), (IsMuon==1.0) &&  (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.5), (IsMuon==1.0) &&  (nShared==0) && ((V2ProbNNmu - V2ProbNNpi) > -0.4), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.2), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.25), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.3), (IsMuon==1.0) &&  (nShared==0) && (V2ProbNNmu > 0.35)]" > logpionstrip21logdown.txt



