
mkdir ~/public_html/DataMCReweighting/
mkdir ~/public_html/DataMCReweighting/1DPPT_2016
mkdir ~/public_html/DataMCReweighting/2DPPT_2016
mkdir ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToReconstQuantities
mkdir ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToTrueQuantities

cp bin/*1D*pdf ~/public_html/DataMCReweighting/1DPPT_2016
cp bin/*ALL*2D*RECO*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToReconstQuantities
cp bin/RATIO*RECO*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToReconstQuantities
cp bin/*ALL*2D*TRUE*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToTrueQuantities
cp bin/RATIO*TRUE*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToTrueQuantities
