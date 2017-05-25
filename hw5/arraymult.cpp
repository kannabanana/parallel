#include "simd.p5.h"
#include <omp.h>

void CMul(float *in1, float* in2, float* out, int size) {
        for(int i = 0; i < size; i++) {
                out[i] = in1[i] * in2[i];
        }
}

void CMulAdd(float *in1, float* in2, float* out, int size) {
	for(int i = 0; i < size; i ++) {
		out[i] = in1[i] * in2[i] + in2[i];
	}
}

int main() {
	printf("Array Size\tSIMD\t\tCPP\tSpeedup\n");
	
	for(int size=1024; size <= 1024*1024*32; size = size*2) {
		printf("%d...",size);
		float *in1 = new float[size];
		float *in2 = new float[size];
		float *in3 = new float[size];
		float *out = new float[size];
		double start_time = omp_get_wtime();
		SimdMul(in1,in2,out,size);	
		double end_time = omp_get_wtime();
		printf("%f...",((float)size)/(-start_time+end_time));

		float one = ((float)size)/(-start_time+end_time);
		start_time = omp_get_wtime();
		CMul(in1,in2,out,size);
		end_time = omp_get_wtime();
		printf("%f...",((float)size)/(-start_time+end_time));
		float two = ((float)size)/(-start_time+end_time);
		printf("%f\n",(one/two));

	}
}
