#!/bin/sh

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logcrossfeedprotonmisaspionstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logcrossfeedprotonmisaspionstrip21logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logcrossfeedprotonmisaspionstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK < 0.0 && DLLp < 5.0]" > logcrossfeedprotonmisaspionstrip21r1logdown.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedpionmisasprotonstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedpionmisasprotonstrip21logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedpionmisasprotonstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "Pi" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedpionmisasprotonstrip21r1logdown.txt



