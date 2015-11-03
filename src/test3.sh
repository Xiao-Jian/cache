make clean
make
./sim_cache 32 4096 4 0 1 perl_trace > output3.txt
diff -iw output3.txt ValidationRun3.txt > debug3
