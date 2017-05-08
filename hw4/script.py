import os

for t in [1,2,4]:
	for p in [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]:
			cmd = "g++ -DNUMT=%d -DNUMPAD=%d hw3.cpp -o prog -lm -fopenmp" %(t,p)
			os.system(cmd)
			cmd = "prog"
			os.system(cmd)
	print
	print
