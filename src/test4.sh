make clean
make
./sim_cache 64 8192 2 1 0 gcc_trace > output4.txt
diff -iw output4.txt ValidationRun4.txt > debug4
