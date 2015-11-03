make
./sim_cache 16 16384 1 0 0 gcc_trace > output.txt
diff -iw output.txt ValidationRun1.txt > debug
