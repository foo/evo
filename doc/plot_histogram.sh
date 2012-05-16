#!/bin/bash
cat $1 > histogram.dat
file="histogram1.gnuplot"
gnuplot $file > tmp.eps
epstopdf tmp.eps --outfile=$2
rm tmp.eps
rm histogram.dat
