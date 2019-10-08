set title "perf"
set xlabel "size"
set ylabel "time (ns)"
set terminal png font " Times_New_Roman,12 "
set key left
set yrange[0: 20881933]
set output filename

if (exist("name3"))\
    plot \
    "out.txt" using 1:2 title name1, \
    "out.txt" using 1:3 title name2  \
else \
    plot \
    "out.txt" using 1:2 title name1, \
    "out.txt" using 1:3 title name2  \
    "out.txt" using 1:4 title name3  \
