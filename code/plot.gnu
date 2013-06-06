#/usr/bin/env gnuplot

set terminal png size 480,240
set logscale xy

set output 'real_graph.png'
plot 'real_graph.txt', 0.0988487*x**(-1.28909)

set output 'simulated_graph.png'
plot 'simulated_graph.txt', 0.0192542*x**(-1.28556)
