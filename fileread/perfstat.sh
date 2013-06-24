#!/usr/bin
#Collect performance stats for each of the methods for reading a file using c++
# Argument is the file to load

for i in {1..6};do
    perf stat -o .lst -d -r 20 ./fileread  
done
