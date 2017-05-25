#!/usr/bin/env bash

echo "Performance Data"
echo "NKB	Local Size	Global Work Groups	GigaMultsPerSecond"

nkb=1

while [ $nkb -lt 65536 ]
do
	g++ -Wno-write-strings -DNKB=${nkb} -DLOCAL_SIZE=32 -fopenmp -lm /usr/lib64/libOpenCL.so first.cpp -o first
	./first 2>tmp
	cat tmp | grep -v "failed"
	rm tmp
	nkb=$((nkb*2))
done
