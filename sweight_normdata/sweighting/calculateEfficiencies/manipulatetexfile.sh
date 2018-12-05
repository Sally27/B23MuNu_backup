#!/bin/bash
for i in  {1..9}
do
    echo $i
    sed -i -e "s/e-0$i/$\\\\times10^{-$i}$/g" bin/EfficiencyComparison_compared_toNormalisation_nove_nicedig.tex
done

