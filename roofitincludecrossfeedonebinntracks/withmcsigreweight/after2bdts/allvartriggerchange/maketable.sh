#!/bin/bash

VAR1=Strip21r1
VAR2=MagUp

cat beg.txt >  STATISTICS$VAR1$VAR2.tex
cat bin/STATISTICS$VAR1$VAR2*.txt >>  STATISTICS$VAR1$VAR2.tex
cat end.txt >>  STATISTICS$VAR1$VAR2.tex

