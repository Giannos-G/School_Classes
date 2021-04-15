#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
	int i;
	int N=100000000;
	double *x1, *x2, *x3, *y;
	double a1= 0.5;
	double a2= 1;
	double a3= 1.5;

	x1 = (double*) malloc(N*sizeof(double));
	x2 = (double*) malloc(N*sizeof(double));
	x3 = (double*) malloc(N*sizeof(double));
	y = (double*) malloc(N*sizeof(double));


	//Do not modify this loop
	for (i=0; i<=N-1; i++)
	{
		x1[i] = (double) i * 0.5;
		x1[i] = (double) i * 0.4; 
		x2[i] = (double) i * 0.8;
		x3[i] = (double) i * 0.2;
		y[i] = 0;
	}

	struct timeval begin,end;
	 begin.tv_usec = 0;
	 begin.tv_sec =0;
	 end.tv_usec = 0;
	 end.tv_sec=0;
	 //Start Counting
	gettimeofday(&begin, NULL);
	/*
	Τhis is the transformed loop of tables.c.
	*/

    for (i = 0; i <= N - 11; i = i + 11) {
      y[i] = y[i] + a1 * x1[i] + a2 * x2[i] + a3 * x3[i];
      y[(i + 1)] = y[(i + 1)] + a1 * x1[(i + 1)] + a2 * x2[(i + 1)] + a3 * x3[(i + 1)];
      y[(i + 2)] = y[(i + 2)] + a1 * x1[(i + 2)] + a2 * x2[(i + 2)] + a3 * x3[(i + 2)];
      y[(i + 3)] = y[(i + 3)] + a1 * x1[(i + 3)] + a2 * x2[(i + 3)] + a3 * x3[(i + 3)];
      y[(i + 4)] = y[(i + 4)] + a1 * x1[(i + 4)] + a2 * x2[(i + 4)] + a3 * x3[(i + 4)];
      y[(i + 5)] = y[(i + 5)] + a1 * x1[(i + 5)] + a2 * x2[(i + 5)] + a3 * x3[(i + 5)];
      y[(i + 6)] = y[(i + 6)] + a1 * x1[(i + 6)] + a2 * x2[(i + 6)] + a3 * x3[(i + 6)];
      y[(i + 7)] = y[(i + 7)] + a1 * x1[(i + 7)] + a2 * x2[(i + 7)] + a3 * x3[(i + 7)];
      y[(i + 8)] = y[(i + 8)] + a1 * x1[(i + 8)] + a2 * x2[(i + 8)] + a3 * x3[(i + 8)];
      y[(i + 9)] = y[(i + 9)] + a1 * x1[(i + 9)] + a2 * x2[(i + 9)] + a3 * x3[(i + 9)];
      y[(i + 10)] = y[(i + 10)] + a1 * x1[(i + 10)] + a2 * x2[(i + 10)] + a3 * x3[(i + 10)];
    }
    for (i = N - ((N - (0)) % 11); i <= N - 1; i = i + 1) 
      y[i] = y[i] + a1 * x1[i] + a2 * x2[i] + a3 * x3[i];

	 //End of counting and time computation
  	gettimeofday(&end, NULL);
  	unsigned long long t = end.tv_sec * 1000000ULL + end.tv_usec - begin.tv_sec * 1000000ULL - begin.tv_usec;
  	printf(" Runtime: %lld us \n", t);
	return 0;

}
