#!/bin/bash

cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/MCSigpreparetuple/bin/Efficiencies.pdf EfficienciesB23muMC.pdf
cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKmc2011strip20r1/bin/Efficiencieschangedname.pdf EfficienciesJpsiKmc2011.pdf
cp /vols/lhcb/ss4314/preparetuplesforBDTfinalallvartrigger/JpsiKmc/bin/Efficiencies.pdf EfficienciesJpsiKmc2012.pdf
cp /vols/lhcb/ss4314/cutonBDTs/CombiBackTonomu1mu3ETAtighterproton/numofeventsleftintuples.pdf numofeventsleftintuplesCOMBI.pdf
cp /vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/numofeventsleftintuples.pdf numofeventsleftintuplesMISID.pdf
cp /vols/lhcb/ss4314/cutonBDTs/CombiBackTonomu1mu3ETAtighterproton/*pdf .
cp /vols/lhcb/ss4314/cutonBDTs/MisidBackTonomu1mu3ETAtighterproton/*pdf .
cp *pdf ~/public_html/SingelEventSensitivity/
