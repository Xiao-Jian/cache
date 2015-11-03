make clean
make
./sim_cache 128 2048 8 0 1 go_trace > output2.txt
diff -iw output2.txt ValidationRun2.txt > debug2
