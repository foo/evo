#!/bin/bash

# usage: ./varianceall.sh <iterations>

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
	if [ -f ${z}${i}v.pdf ] ; then
		echo "Graph ${z}${i}v.pdf already exists. Skipping to next test."
		continue	
	fi
	if [ ! -f ../in/${z}${i}.in ] ; then
		echo "Test ${z}${i} does not exist. Skipping to next test."
		continue	
	fi
		
	echo "Executing evo.e for test $z$i"
	../src/evo.e -v -i $1 < ../in/$z$i.in > tmp.res
	./plot_graph.sh tmp.res ${z}${i}v.pdf
done

rm tmp.res
