#!/bin/bash

# usage: evals_to_optimum.sh <test> <percentage to optimum> 

s="t"$1
opt=$(grep ${s:0:4} ../in/optimal-cmax | cut -f2)
prec=$(echo "scale=2;$opt + ($opt * $2)" | bc)
precfinal=${prec%.*}
touch tmpevals.dat
../src/evo.e -o $precfinal -p 10 < ../in/$1.in >> tmpevals.dat
../src/evo.e -o $precfinal -p 20 < ../in/$1.in >> tmpevals.dat
../src/evo.e -o $precfinal -p 50 < ../in/$1.in >> tmpevals.dat
../src/evo.e -o $precfinal -p 100 < ../in/$1.in >> tmpevals.dat
../src/evo.e -o $precfinal -p 200 < ../in/$1.in >> tmpevals.dat
../src/evo.e -o $precfinal -p 500 < ../in/$1.in >> tmpevals.dat
../src/evo.e -o $precfinal -p 1000 < ../in/$1.in >> tmpevals.dat
file="histogram2.gnuplot"
gnuplot $file > tmp.eps
epstopdf tmp.eps --outfile=${1}p.pdf
rm tmpevals.dat
rm tmp.eps

