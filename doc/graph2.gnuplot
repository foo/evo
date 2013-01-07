set autoscale
set terminal postscript eps
set size 0.5,0.5
set style line 1 lt 1 lc rgb "red" lw 1
set style line 2 lt 1 lc rgb "green" lw 1
plot 'graph.dat' using 1:2 notitle with lines ls 1, \
     'graph.dat' using 1:3 notitle with lines ls 2