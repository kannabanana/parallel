import os

for t in [1,2,3,4]:
	for s in [x*x for x in range(4,10)]:
		cmd = "g++ -DNUMNODES=%d -DNUMT=%d hw1.c -o prog -lm -fopenmp" %(s,t)
		os.system(cmd)
		cmd = "prog"
		os.system(cmd)
	print
	print
