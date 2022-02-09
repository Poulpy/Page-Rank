set term png size 1900,1000 enhanced font "Terminal,20"

set title "Execution time in milliseconds as a function of damping factor"

set xlabel "Damping factor"
set ylabel "Execution time (ms)"

plot ARG1 using 2:1 with linespoints
