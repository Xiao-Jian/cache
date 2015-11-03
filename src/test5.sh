make clean
make
./sim_cache 32 1024 4 1 1 go_trace > output5.txt
diff -iw output5.txt ValidationRun5.txt > debug5
