set autoscale
set terminal postscript eps
set size 0.5,0.5
set style line 1 lt 1 lc rgb "red" lw 1
set style line 2 lt 1 lc rgb "orange" lw 1
set style line 3 lt 1 lc rgb "green" lw 1
set label 1 'PMX' at graph 0.8, graph 0.9 tc rgb "red"
set label 2 'OX' at graph 0.8, graph 0.8 tc rgb "orange"
set label 3 'CX' at graph 0.8, graph 0.7 tc rgb "green"
plot 'graph.dat' using 1:2 notitle with lines ls 1, \
     'graph.dat' using 1:3 notitle with lines ls 2, \
     'graph.dat' using 1:4 notitle with lines ls 3
