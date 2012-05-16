set autoscale
set terminal postscript eps
set size 0.5,0.5
set style fill solid border -1
set style data histogram
set style histogram cluster gap 1
set yrange [0:*]
set ylabel "Succesful crossovers"
set xlabel "Number of crossovers"

set offsets graph 0, graph 0.2, graph 0.2, 0.05 
plot 'histogram.dat' using 2 t "OX" lc rgb "orange" lt 1, '' using 3 t "CX" lc rgb "green" lt 1, '' using 4:xtic(1) t "PMX" lc rgb "red" lt 1

