#!/bin/sh

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logcrossfeedprotonmisaskaonstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logcrossfeedprotonmisaskaonstrip21logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logcrossfeedprotonmisaskaonstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "P" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLK > 0.0 && ((DLLp - DLLK) < 5.0)]" > logcrossfeedprotonmisaskaonstrip21r1logdown.txt


python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedkaonmisasprotonstrip21logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedkaonmisasprotonstrip21logdown.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagUp" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedkaonmisasprotonstrip21r1logup.txt

python $PIDPERFSCRIPTSROOT/scripts/python/MultiTrack/MakePerfHistsRunRange.py -Z ""  "21r1" "MagDown" "K" "[IsMuon==0.0 && InMuonAcc==1.0 && DLLp > 0.0 && ((DLLp - DLLK) > 0.0)]" > logcrossfeedkaonmisasprotonstrip21r1logdown.txt



