#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;


#define numThreads 1
#define numSubdivisions 4
const double A = 0.;
const double B = 5;

double dx = (B-A)/(float)(numSubdivisions-1);

omp_set_num_threads(numThreads);
double sum = (A+B)/2.;

#pragma omp parallel for default(none),shared(dx),reduction(+:sum)
for (int i = 1;i<numSubdivisions-1;++i)
{
	double x = A+dx*(float)i;
	double f = x;
	sum += f;

}

sum += dx;
cout << sum << endl;
