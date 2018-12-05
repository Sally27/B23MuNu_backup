
mkdir ~/public_html/DataMCReweighting/
mkdir ~/public_html/DataMCReweighting/1DPPT
mkdir ~/public_html/DataMCReweighting/2DPPT
mkdir ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToReconstQuantities_alt1
mkdir ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToTrueQuantities_alt1

cp bin/*1D*alt1*pdf ~/public_html/DataMCReweighting/1DPPT
cp bin/*ALL*2D*RECO*alt1*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToReconstQuantities_alt1
cp bin/RATIO*RECO*alt1*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToReconstQuantities_alt1
cp bin/*ALL*2D*TRUE*alt1*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToTrueQuantities_alt1
cp bin/RATIO*TRUE*alt1*pdf ~/public_html/DataMCReweighting/2DPPT/ReweightedRecoAndAppliedToTrueQuantities_alt1
