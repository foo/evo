#!/bin/bash

# usage: ./histogramall.sh <iterations>

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
	if [ -f ${z}${i}h.pdf ] ; then
		echo "Graph ${z}${i}h.pdf already exists. Skipping to next test."
		continue	
	fi
	if [ ! -f ../in/${z}${i}.in ] ; then
		echo "Test ${z}${i} does not exist. Skipping to next test."
		continue	
	fi
		
	echo "Executing evo.e for test $z$i"
	../src/evo.e -c -i $1 < ../in/$z$i.in > tmp.res
	./plot_histogram.sh tmp.res ${z}${i}h.pdf
done

rm tmp.res
