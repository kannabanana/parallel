import os

for t in [1,2,4]:
	cmd = "g++ -DNUMT=%d hw2.c -o prog -lm -fopenmp" %(t)
	os.system(cmd)
	cmd = "prog"
	os.system(cmd)
print
print
