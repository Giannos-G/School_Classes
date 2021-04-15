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
	Τhis is the basic loop of tables.c. Isolate it in file tables_orio.c,
	in which all the parameters for Design Space Exploration (DSE) and loop 
	transfornations should be defined.
	*/

	for (i=0; i<=N-1; i++)
	{
		//This loop needs to be modified after Orio's execution...
		y[i] = y[i] + a1*x1[i] + a2*x2[i] + a3*x3[i];
	}

	 //End of counting and time computation
  	gettimeofday(&end, NULL);
  	unsigned long long t = end.tv_sec * 1000000ULL + end.tv_usec - begin.tv_sec * 1000000ULL - begin.tv_usec;
  	printf(" Runtime: %lld us \n", t);
	return 0;

}
