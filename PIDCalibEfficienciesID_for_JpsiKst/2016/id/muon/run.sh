python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Brunel_IsMuon==1.0" -Z ""  "Turbo16" "MagDown" "Mu" "[(Brunel_MC15TuneV1_ProbNNmu > 0.5)]" >logmuonstripTurbo16logdown.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -c "Brunel_IsMuon==1.0" -Z ""  "Turbo16" "MagUp" "Mu" "[(Brunel_MC15TuneV1_ProbNNmu > 0.5)]" > logmuonstripTurbo16logup.txt






