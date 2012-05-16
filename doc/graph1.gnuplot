set autoscale
set terminal postscript eps
set size 0.5,0.5
set multiplot
plot 'graph.dat' using 1:2 notitle with lines
