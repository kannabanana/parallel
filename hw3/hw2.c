#include <stdlib.h>
#include <cstidio>
#include <omp.h>

using namespace std;


#define ARRAYSIZE	32*1024
#define NUMT		2

float Ranf( float low, float high )
{
	float r = (float) rand();		// 0 - RAND_MAX

	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}



int main()
{
	int i;
	float Array[i] = ranf(-1.f,1.f);
	int len = length(Array);

	#pragma omp parallel for default(none),schedule(static,1)
	for(int k=0;k<len-1;++k)
	{
		float prod = 1;
		for (int j=0;j<i;++j)
		{
			prod *= Array[j];
		}

	}



long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE+1) / 2;  // count of how many multiplications were done:
        fprintf( stderr, "Threads = %2d; ChunkSize = %5d; Scheduling=static ; MegaMults/sec = %10.2lf\n", NUMT, CHUNKSIZE, (double)numMuled/(time1-time0)/1000000. );


	return 0;
}
