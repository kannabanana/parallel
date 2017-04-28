import os

for t in [1,2,4]:
	for c in [1,4096]:
		cmd = "g++ -DNUMT=%d -DCHUNKSIZE=%d hw2.c -o prog -lm -fopenmp" %(t,c)
		os.system(cmd)
		cmd = "prog"
		os.system(cmd)
	print
	print
