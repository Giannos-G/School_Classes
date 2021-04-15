
//#include <stdio.h>
//#include <stdlib.h>
#include "phods_optimized_2dimensions.c"

// Global Variables

	long i = 0; //counter for average time

	long maxtime = 0;
	int a;
	long mintime =0; 
	long averagetime =0;
	long sum =0; 
	int Bxdim[] = {	1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 36, 48, 72, 144};  // Divisors of N 
	int Bydim[] = {1, 2, 4, 8, 11, 16, 22, 44, 88, 176}; 					// Divisors of M
	int Opt_Bx = 0;
	int Opt_By = 0;
	int MinTime = 0;

// Calculations for Time 
void RunTimer (unsigned long long time, int repeat){ 
	if (repeat=1) mintime = time; //initialization
	if (time>maxtime) maxtime = time;
	if (time<mintime) mintime = time;
	sum = sum + time;
}


int main(){
	
	//int UserSize = atoi (argv[1]); // User Inputs the Block Size
	for (int xdimension=0; xdimension<15; xdimension++){ // For each x-dimension
		Bx = Bxdim[xdimension];
  		for (int ydimension =0; ydimension<10; ydimension++){ 	// For each y-dimension

  			By = Bydim[ydimension];
  			printf ("Bx: %d \n", Bx);
  			printf ("By: %d \n", By);

			// Executes phods_optimized_2dimensions.c 10 times
			for (int j=0; j<10; j++){
				mainexecutable();
				RunTimer(timetobesentfunct(),j);
			}
			printf("Maxtime = %ld\n", maxtime );
			printf("Mintime = %ld\n", mintime );
			averagetime = sum/10;

			//Set to zero to be ready for the next iteration
			sum=0;
			maxtime=0;
			mintime=0;

			printf("Averagetime = %ld\n", averagetime );

			//Initialization of MinTime
			if ((xdimension ==0) && (ydimension==0)) MinTime = averagetime;

			// Calculations to find the minimum average time of all the options
			else {
				if ((averagetime<MinTime)/*&&(averagetime>0)*/) {
				MinTime = averagetime;
				Opt_Bx = Bx;
				Opt_By = By;
			}
		}

		}
	}
	// Final Results
	printf ("Opt. Bx: %d \n", Opt_Bx);
	printf ("Opt. By: %d \n", Opt_By);
	printf ("Minimum Average Time %d \n", MinTime);

}
