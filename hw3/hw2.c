#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <omp.h>

using namespace std;


#define ARRAYSIZE	32*1024
//#define NUMT		2
//#define CHUNKSIZE	1
//#define SCHEDULE	static
float ARRAY[ARRAYSIZE];

float Ranf( float low, float high )
{
	float r = (float) rand();		// 0 - RAND_MAX

	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}



int main()
{
	int i = 0;
	for (i=0;i<ARRAYSIZE-1;++i)
	{
		ARRAY[i] = Ranf(-1.f,1.f);

	}

	int time0 = omp_get_wtime();
	float prod = 1;

	#pragma omp parallel for private(prod),schedule(SCHEDULE,CHUNKSIZE)
	for(int k=0;k<ARRAYSIZE-1;++k)
	{
		prod = 1;
		for (int j=0;j<k;++j)
		{
			prod *= ARRAY[j];
		}

	}

	int time1 = omp_get_wtime();

long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE+1) / 2;  // count of how many multiplications were done:
        fprintf( stderr, "Threads = %2d; ChunkSize = %5d; Scheduling=static ; MegaMults/sec = %10.2lf\n", NUMT, CHUNKSIZE, (double)numMuled/(time1-time0)/1000000. );


	return 0;
}
