#!bin/bash/

VAR1=pionproton

mkdir ~/public_html/misidprocedure/mcnsharedremoved

mkdir ~/public_html/misidprocedure/mcnsharedremoved/$VAR1

cp bin/*pdf ~/public_html/misidprocedure/mcnsharedremoved/$VAR1/
cp bin/*tex ~/public_html/misidprocedure/mcnsharedremoved/$VAR1/

mkdir ~/public_html/misidprocedure/mcnsharedremoved/$VAR1/efficiencies/

cp *pdf  ~/public_html/misidprocedure/mcnsharedremoved/$VAR1/efficiencies/
