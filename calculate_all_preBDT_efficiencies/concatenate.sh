
cat PIDtables/beg.txt PIDtables/*1.5_5.txt PIDtables/end.txt > PIDtables/all_1.5_5.tex
#cat PIDtables/beg.txt PIDtables/*2.375_3.25.txt PIDtables/end.txt > PIDtables/all_2.375_3.25.tex
#cat PIDtables/beg.txt PIDtables/*3.25_4.125.txt PIDtables/end.txt > PIDtables/all_3.25_4.125.tex
#cat PIDtables/beg.txt PIDtables/*4.125_5.txt PIDtables/end.txt > PIDtables/all_4.125_5.tex

cd PIDtables; for i in *.tex; do pdflatex $i;done
