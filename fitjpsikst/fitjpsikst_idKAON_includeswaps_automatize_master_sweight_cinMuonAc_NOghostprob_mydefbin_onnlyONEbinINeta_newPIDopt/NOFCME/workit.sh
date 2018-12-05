Cleaning all the directories
4

[1mRooFit v3.60 -- Developed by Wouter Verkerke and David Kirkby[0m 
                Copyright (C) 2000-2013 NIKHEF, University of California & Stanford University
                All rights reserved, please read http://roofit.sourceforge.net/license.txt

I am bad!
P binning:   3000,  9300,  15600,  19000,  24400,  29800,  35200,  40600,  46000,  51400,  56800,  62200,  67600,  73000,  78400,  83800,  89200,  94600,  100000,.
ETA binning:   1.5,  5,.
ntracks binning:   0,  50,  200,  300,  500,.
Number of Xbins: 18
Number of Ybins: 1
Down -2388.89
Up 3000
Filling tree with new var... done! New tree has: 128083 entries.
BLABLA: B0_DTFM_M_zero>5150 && B0_DTFM_M_zero<5450
[#1] INFO:Eval -- RooTreeDataStore::loadValues(data) Ignored 461 out of range events
[#1] INFO:ObjectHandling -- RooWorkspace::import(workspaceData) importing RooRealVar::B0_DTFM_M_zero
[#1] INFO:ObjectHandling -- RooWorkspace::import(workspaceData) importing RooRealVar::mcweight
[#1] INFO:ObjectHandling -- RooWorkspace::import(workspaceData) importing dataset data
Number of entries before Pi_P>3000 && Pi_P<9300 and Pi_ETA>1.5 && Pi_ETA<5 and K_PIDK>0 is 355662
Number of entries after Pi_P>3000 && Pi_P<9300 and Pi_ETA>1.5 && Pi_ETA<5 and K_PIDK>0 is 128083
Workspace containing data ready:

RooWorkspace(workspaceData) workspaceData contents

variables
---------
(B0_DTFM_M_zero,mcweight)

datasets
--------
RooDataSet::data(B0_DTFM_M_zero)

Start Signal Component fit
My dataset is weighted!
PartyTime
[#1] INFO:InputArguments -- RooAbsData::plotOn(data) INFO: dataset has non-integer weights, auto-selecting SumW2 errors instead of Poisson errors
[#1] INFO:NumericIntegration -- RooRealIntegral::init(sig_Int[B0_DTFM_M_zero]) using numeric integrator RooIntegrator1D to calculate Int(B0_DTFM_M_zero)
[#1] INFO:Minization -- RooMinuit::optimizeConst: activating const optimization
 **********
 **   13 **MIGRAD        4500           1
 **********
 FIRST CALL TO USER FUNCTION AT NEW START POINT, WITH IFLAG=4.
 START MIGRAD MINIMIZATION.  STRATEGY  1.  CONVERGENCE WHEN EDM .LT. 1.00e-03
 FCN=229985 FROM MIGRAD    STATUS=INITIATE       40 CALLS          41 TOTAL
                     EDM= unknown      STRATEGY= 1      NO ERROR MATRIX       
  EXT PARAMETER               CURRENT GUESS       STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  a1coeff      2.75000e+00   4.00000e-01   2.03041e-01   6.79991e+02
   2  a2coeff      2.16640e+00   4.10000e-01   2.31953e-01  -8.52981e+01
   3  fb          -2.20960e-04   1.80000e-05   2.02684e-01   1.51480e+00
   4  l           -2.44000e+00   5.00000e-01   2.23967e-01  -4.02863e+02
   5  mean         5.28000e+03   4.00000e-01   2.01358e-01   1.92249e+02
   6  n1coeff      1.41900e+00   2.09500e-01   1.76679e-01   3.42980e+02
   7  n2coeff      2.70000e+00   5.70000e-01   2.02181e-01  -3.09430e-01
   8  sigma        8.37000e+00   1.20000e+00   2.02541e-01   7.92628e+02
   9  zeta         1.00000e-05   4.99500e-06   1.63610e-03   2.64283e-06
                               ERR DEF= 0.5
 MIGRAD FAILS TO FIND IMPROVEMENT
 COVARIANCE MATRIX CALCULATED SUCCESSFULLY
 FCN=229893 FROM HESSE     STATUS=OK             75 CALLS         173 TOTAL
                     EDM=17.8485    STRATEGY= 1      ERROR MATRIX ACCURATE 
  EXT PARAMETER                                   STEP         FIRST   
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
   1  a1coeff      2.48410e+00   1.10636e-01   4.88594e-03   1.28082e+01
   2  a2coeff      2.19624e+00   6.55039e-02   7.17501e-03  -2.22435e+01
   3  fb          -2.50978e-04   1.26155e-04   5.00000e-01   2.33845e-01
   4  l           -2.32059e+00   1.20646e-01   4.92708e-03   5.67158e+01
   5  mean         5.27995e+03   3.22909e-02   4.86735e-03   1.49538e+01
   6  n1coeff      1.29018e+00   1.07497e-01   9.68880e-03  -1.89207e+01
   7  n2coeff      2.64046e+00   1.21107e-01   8.75457e-03   2.38509e+01
   8  sigma        8.28134e+00   1.30507e-01   1.78333e-03   2.72274e+01
   9  zeta         2.12344e-02   1.66304e-01   5.00000e-01   1.94043e-02
                               ERR DEF= 0.5
