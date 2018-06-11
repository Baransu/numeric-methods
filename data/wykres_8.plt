# FLOAT
set xrange [-16:0]
set yrange [-8:0.5]
set terminal png size 1366,768
set output "data/Wykres_float.png"
set title 'Wykres dla float'
set ylabel 'log10(|błędu|)'
set xlabel 'log10(h)
set grid
plot \
 "data/data_f.txt" using 1:2 with lines title "Pocz progresywna 2pkt",\
 "data/data_f.txt" using 1:3 with lines title "Pocz progresywna 3pkt",\
 "data/data_f.txt" using 1:4 with lines title "Srod progresywna 2pkt",\
 "data/data_f.txt" using 1:5 with lines title "Srod centralna",\
 "data/data_f.txt" using 1:6 with lines title "Srod wsteczna 2pkt",\
 "data/data_f.txt" using 1:7 with lines title "Kon wsteczna 2pkt",\
 "data/data_f.txt" using 1:8 with lines title "Kon wsteczna 3pkt",\

# DOUBLE

set xrange [-16:0]
set yrange [-12.5:0.5]
set terminal png size 1366,768
set output "data/Wykres_double.png"
set title 'Wykres dla double'
set ylabel 'log10(|błędu|)'
set xlabel 'log10(h)
set grid
plot \
 "data/data_d.txt" using 1:2 with lines title "Pocz progresywna 2pkt",\
 "data/data_d.txt" using 1:3 with lines title "Pocz progresywna 3pkt",\
 "data/data_d.txt" using 1:4 with lines title "Srod progresywna 2pkt",\
 "data/data_d.txt" using 1:5 with lines title "Srod centralna",\
 "data/data_d.txt" using 1:6 with lines title "Srod wsteczna 2pkt",\
 "data/data_d.txt" using 1:7 with lines title "Kon wsteczna 2pkt",\
 "data/data_d.txt" using 1:8 with lines title "Kon wsteczna 3pkt"


# FLOAT_DOUBLE
set xrange [-16:0]
set yrange [-12.5:0.5]
set terminal png size 1366,768
set output "data/Wykresy.png"
set title 'Wykres dla float i double'
set ylabel 'log10(|błędu|)'
set xlabel 'log10(h)
set grid
plot \
 "data/data_f.txt" using 1:2 with lines title "FL Pocz progresywna 2pkt",\
 "data/data_f.txt" using 1:3 with lines title "FL Pocz progresywna 3pkt",\
 "data/data_f.txt" using 1:4 with lines title "FL Srod progresywna 2pkt",\
 "data/data_f.txt" using 1:5 with lines title "FL Srod centralna",\
 "data/data_f.txt" using 1:6 with lines title "FL Srod wsteczna 2pkt",\
 "data/data_f.txt" using 1:7 with lines title "FL Kon wsteczna 2pkt",\
 "data/data_f.txt" using 1:8 with lines title "FL Kon wsteczna 3pkt",\
 "data/data_d.txt" using 1:2 with lines title "DB Pocz progresywna 2pkt",\
 "data/data_d.txt" using 1:3 with lines title "DB Pocz progresywna 3pkt",\
 "data/data_d.txt" using 1:4 with lines title "DB Srod progresywna 2pkt",\
 "data/data_d.txt" using 1:5 with lines title "DB Srod centralna",\
 "data/data_d.txt" using 1:6 with lines title "DB Srod wsteczna 2pkt",\
 "data/data_d.txt" using 1:7 with lines title "DB Kon wsteczna 2pkt",\
 "data/data_d.txt" using 1:8 with lines title "DB Kon wsteczna 3pkt"

