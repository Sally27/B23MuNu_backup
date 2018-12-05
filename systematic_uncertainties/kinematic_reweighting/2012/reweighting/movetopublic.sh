
mkdir ~/public_html/DataMCReweighting/
mkdir ~/public_html/DataMCReweighting/1DPPT
mkdir ~/public_html/DataMCReweighting/2DPPT
mkdir ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToReconstQuantities
mkdir ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToTrueQuantities

cp bin/*1D*pdf ~/public_html/DataMCReweighting/1DPPT
cp bin/*ALL*2D*RECO*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToReconstQuantities
cp bin/RATIO*RECO*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToReconstQuantities
cp bin/*ALL*2D*TRUE*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToTrueQuantities
cp bin/RATIO*TRUE*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToTrueQuantities
