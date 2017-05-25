#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <omp.h>

struct s
{
	float value;
	int pad[NUMPAD];
} Array[4];



int main()
{	

	omp_set_num_threads( NUMT );

	const int SomeBigNumber = 100000000;	// keep < 2B

	double time0 = omp_get_wtime();
	

	#pragma omp parallel for
	for( int i = 0; i < 4; i++ )
	{
		float tmp = Array[i].value;
		unsigned int seed = 0;		// automatically private
		for( unsigned int j = 0; j < SomeBigNumber; j++ )
		{
			tmp = tmp + (float)rand_r( &seed );
		}
		Array[i].value = tmp;
	}

	double time1 = omp_get_wtime();
//	long int numMuled = (long int)4 * (long int)(4) / 2;  // count of how many multiplications were done:

//	double total = double(4*4)/(time1-time0)/1000000.;
//        fprintf( stderr, "Threads = %2d; MegaMults/sec = %10.2lf\n", NUMT, total );

	fprintf(stderr, "MegaAdd/sec = %10.2lf\n\n",(double)SomeBigNumber/(time1-time0)/1000000.);


}
