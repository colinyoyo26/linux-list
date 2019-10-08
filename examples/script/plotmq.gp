set title "perf"
set xlabel "size"
set ylabel "time (ns)"
set terminal png font " Times_New_Roman,12 "
set key left
set yrange[0: 20881933]
set output "mqcmp.png"

plot \
"out.txt" using 1:2 title "merge-sort", \
"out.txt" using 1:3 title "quick-sort"
