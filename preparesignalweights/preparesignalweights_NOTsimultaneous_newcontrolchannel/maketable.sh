#!/bin/bash

VAR1=Strip21
VAR2=MagUp
VAR3=Strip21_MagUp

cat beg.txt >  STATISTICS_$VAR3.tex
cat bin/STATISTICS_$VAR3*.txt >>  STATISTICS_$VAR3.tex
cat end.txt >>  STATISTICS_$VAR3.tex

