#!/bin/bash

#find . -name "*tex" -exec sed -i "s,$$$_$$$,_,g" '{}' +
echo "Putting backslash"
find . -name "*tex" -exec sed -i "s,_,\\\_,g" '{}' +

echo "Removing Hlt2 line since trigger now means hlt2 cut"
find . -name "*tex" -exec sed -i '30,31d;' '{}' +

for f in *tex
do
	latex $f
done
#find . -name "*tex" -exec sed -i "s/(Bplus$$_$$Hlt2TopoMu2BodyDecision$$_$$TOS==1.0) || (Bplus$$_$$Hlt2TopoMu3BodyDecision$$_$$TOS==1.0) || (Bplus$$_$$Hlt2DiMuonDetachedDecision$$_$$TOS==1.0) || (Bplus$$_$$Hlt2DiMuonDetachedHeavyDecision$$_$$TOS==1.0)/trigger/g" '{}' +

