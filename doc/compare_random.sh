#!/bin/bash

# usage : ./compare_random.sh <test number> <iterations>

if [ ! -f ../in/$1.in ] ; then
	echo "Test $1 doesn't exist"
	exit 1
fi

touch makefile.tmp
num=$1
iter=$2

echo "${num}ao.res: ../in/${num}.in" >> makefile.tmp
echo "	../src/brute.e -e 100 -i ${iter}00 < $< > \$@" >> makefile.tmp
echo "${num}bo.res: ../in/${num}.in" >> makefile.tmp
echo "	../src/evo.e -e avg -i ${iter} -x pmx -p 100 < $< > \$@" >> makefile.tmp
echo "${num}o.res: ${num}ao.res ${num}bo.res" >> makefile.tmp
echo "	./joinN.sh ${num}ao.res ${num}bo.res > \$@" >> makefile.tmp
echo "${num}o.pdf: ${num}o.res" >> makefile.tmp
echo "	./plot_graph_optimum.sh $< \$@" >> makefile.tmp

make ${num}o.pdf -f makefile.tmp
rm makefile.tmp
