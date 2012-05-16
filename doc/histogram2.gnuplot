set autoscale
set terminal postscript eps
set size 0.5,0.5
set style fill solid border -1
set style data histogram
set style histogram cluster gap 2
set yrange [0:*]
set ylabel "Number of evaluations"
set xlabel "Population size"

set offsets graph 0, graph 0.2, graph 0.2, 0.05 
plot 'tmpevals.dat' using 2:xtic(1) t "evals" lc rgb "red" lt 1
