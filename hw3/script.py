import os

for t in [1,2,4,6,8,10,12,14,16]:
	for c in [1,4096]:
		for s in ['static','dynamic']: 
			cmd = "g++ -DNUMT=%d -DCHUNKSIZE=%d -DSCHEDULE=%s hw2.c -o prog -lm -fopenmp" %(t,c,s)
			os.system(cmd)
			cmd = "prog"
			os.system(cmd)
	print
	print
