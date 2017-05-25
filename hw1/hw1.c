#include <iostream>
#include <cstdio>
#include <omp.h>

using namespace std;

#define XMIN	 0.
#define XMAX	 3.
#define YMIN	 0.
#define YMAX	 3.

#define TOPZ00  0.
#define TOPZ10  1.
#define TOPZ20  0.
#define TOPZ30  0.

#define TOPZ01  1.
#define TOPZ11  6.
#define TOPZ21  1.
#define TOPZ31  0.

#define TOPZ02  0.
#define TOPZ12  1.
#define TOPZ22  0.
#define TOPZ32  4.

#define TOPZ03  3.
#define TOPZ13  2.
#define TOPZ23  3.
#define TOPZ33  3.

#define BOTZ00  0.
#define BOTZ10  -3.
#define BOTZ20  0.
#define BOTZ30  0.

#define BOTZ01  -2.
#define BOTZ11  10.
#define BOTZ21  -2.
#define BOTZ31  0.

#define BOTZ02  0.
#define BOTZ12  -5.
#define BOTZ22  0.
#define BOTZ32  -6.

#define BOTZ03  -3.
#define BOTZ13   2.
#define BOTZ23  -8.
#define BOTZ33  -3.
#define NUMTOTAL 10.


float Height( int iu, int iv )	
{
	float u = (float)iu / (float)(NUMNODES-1);
	float v = (float)iv / (float)(NUMNODES-1);


	float bu0 = (1.-u) * (1.-u) * (1.-u);
	float bu1 = 3. * u * (1.-u) * (1.-u);
	float bu2 = 3. * u * u * (1.-u);
	float bu3 = u * u * u;

	float bv0 = (1.-v) * (1.-v) * (1.-v);
	float bv1 = 3. * v * (1.-v) * (1.-v);
	float bv2 = 3. * v * v * (1.-v);
	float bv3 = v * v * v;



	float top =       bu0 * ( bv0*TOPZ00 + bv1*TOPZ01 + bv2*TOPZ02 + bv3*TOPZ03 )
		+ bu1 * ( bv0*TOPZ10 + bv1*TOPZ11 + bv2*TOPZ12 + bv3*TOPZ13 )
		+ bu2 * ( bv0*TOPZ20 + bv1*TOPZ21 + bv2*TOPZ22 + bv3*TOPZ23 )
		+ bu3 * ( bv0*TOPZ30 + bv1*TOPZ31 + bv2*TOPZ32 + bv3*TOPZ33 );

	float bot =       bu0 * ( bv0*BOTZ00 + bv1*BOTZ01 + bv2*BOTZ02 + bv3*BOTZ03 )
		+ bu1 * ( bv0*BOTZ10 + bv1*BOTZ11 + bv2*BOTZ12 + bv3*BOTZ13 )
		+ bu2 * ( bv0*BOTZ20 + bv1*BOTZ21 + bv2*BOTZ22 + bv3*BOTZ23 )
		+ bu3 * ( bv0*BOTZ30 + bv1*BOTZ31 + bv2*BOTZ32 + bv3*BOTZ33 );

	return top - bot;

}


float Height( int, int );

int main( int argc, char *argv[ ] )
{


	float full_area = ( ((XMAX-XMIN)/(float)(NUMNODES-1)) * ((YMAX - YMIN )/(float)(NUMNODES-1)) );
	float edge_area = ( ((XMAX-XMIN)/(float)(NUMNODES-1)) * ((YMAX - YMIN )/(float)(NUMNODES-1)) ) / 2;
	float corner_area = ( ((XMAX-XMIN)/(float)(NUMNODES-1)) * ((YMAX - YMIN )/(float)(NUMNODES-1)) ) / 4;



	omp_set_num_threads( NUMT );



	double maxMegaHeights = 0.;
	double sum_volume = 0.;
	float total_volume = 0.0;
	
	for (int count=0;count<NUMTOTAL;count++)
	{
		total_volume = 0.0;
		int edge_node = NUMNODES - 1;
		double begin = omp_get_wtime();

		#pragma omp parallel for default(none),shared(corner_area,edge_node,full_area,edge_area),reduction(+:total_volume) 
		for(int i=0;i < NUMNODES*NUMNODES; i++)
		{


			int iu = i % NUMNODES;
			int iv = i / NUMNODES;
			float volume = 0.0;


			//every possibility of edge case
			if (iu == 0 && (iv != edge_node && iv != 0))
				volume += Height(iu,iv)*edge_area;
			else if (iu == edge_node && (iv != edge_node && iv != 0))
				volume += Height(iu,iv)*edge_area;
			else if (iv == 0 && (iu != edge_node && iu != 0))
				volume += Height(iu,iv)*edge_area;
			else if (iv == edge_node && (iu != edge_node && iu != 0))
				volume += Height(iu,iv)*edge_area;
			else
				volume += Height(iu,iv)*full_area;


			//there are only four corner pieces
			if (iu == edge_node && iv == edge_node)
				volume += (Height(iu,iv)*corner_area);
			else if ((iu == 0) && (iv == 0))
				volume += (Height(iu,iv)*corner_area);
			else if (iu == edge_node && iv == 0)
				volume += Height(iu,iv)*corner_area;
			else if (iu == 0 && iv == edge_node)
				volume += Height(iu,iv)*corner_area;

			//update volume
			total_volume += volume;
		}
		
		double end = omp_get_wtime();

		double Volumeunits = (double)(NUMNODES*NUMNODES)/(end-begin)/1000000.;
		sum_volume += Volumeunits;
		if (Volumeunits > maxMegaHeights)
			maxMegaHeights = Volumeunits;
	}

	double avgMegaHeights = sum_volume / NUMTOTAL;
	
	fprintf(stdout,"%8.3lf",maxMegaHeights);
}
