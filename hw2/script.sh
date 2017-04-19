#!/bin/bash

#number of threads: 
for t in 1 2 4 6 8
do
	echo NUMT = $t
	# number of subdivisions:
	for s in 1 10 50 100 500 1000 5000 10000 
	do
		echo NUMNODES = $s
		g++ -DNUMNODES=$s -DNT=$t hw1.cpp -o hw1 -lm -fopenmp 
		./hw1
	done 
done

