
mkdir ~/public_html/DataMCReweighting/
mkdir ~/public_html/DataMCReweighting/1DPPT_2016
mkdir ~/public_html/DataMCReweighting/2DPPT_2016
mkdir ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToReconstQuantities_alt2
mkdir ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToTrueQuantities_alt2

cp bin/*1D*alt2*pdf ~/public_html/DataMCReweighting/1DPPT_2016
cp bin/*ALL*2D*RECO*alt2*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToReconstQuantities_alt2
cp bin/RATIO*RECO*alt2*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToReconstQuantities_alt2
cp bin/*ALL*2D*TRUE*alt2*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToTrueQuantities_alt2
cp bin/RATIO*TRUE*alt2*pdf ~/public_html/DataMCReweighting/2DPPT_2016/ReweightedRecoAndAppliedToTrueQuantities_alt2
