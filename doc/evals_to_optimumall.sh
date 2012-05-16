#!/bin/bash

# usage: ./histogramall.sh <percentage to optimum>   
# 5% = 0.05,  10% = 0.1,   100% = 1

function zeros {
	if [ $1 -lt 10 ] ; then
		zret="00"	
	else
		if [ $1 -lt 100 ] ; then
			zret="0"
		else
			zret=""
		fi
	fi
}

for i in {1..100}; do
	zeros $i	
	z=$zret
	if [ -f ${z}${i}p.pdf ] ; then
		echo "Histogram ${z}${i}p.pdf already exists. Skipping to next test."
		continue	
	fi
	if [ ! -f ../in/${z}${i}.in ] ; then
		echo "Test ${z}${i} does not exist. Skipping to next test."
		continue	
	fi

	echo "Building histogram for for test $z$i"
	./evals_to_optimum.sh ${z}${i} $1
done
