make clean
make
./sim_cache 16 16384 1 0 0 gcc_trace > output1.txt
diff -iw output1.txt ValidationRun1.txt > debug1
