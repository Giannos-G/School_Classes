
//#include <stdio.h>
//#include <stdlib.h>
#include "phods_optimized.c"

// Global Variables

	long i = 0; //counter for average time
	long maxtime = 0;
	int a;
	long mintime =0; 
	long averagetime =0;
	long sum =0; 

// Calculations 
void RunTimer (long time){
	i++;
	if (i=1) mintime = time; 
	if (time>maxtime) maxtime = time;
	if (time<mintime) mintime = time;
	sum = sum + time;
}


int main(int argc, char *argv[]){
	// Executes phods.c 10 times
	int UserSize = atoi (argv[1]); // User Inputs the Block Size

		for (int j=0; j<10; j++){
			mainexecutable(UserSize);
			RunTimer(timetobesentfunct());
		}
		printf("Maxtime = %ld\n", maxtime );
		printf("Mintime = %ld\n", mintime );
		averagetime = sum/10;
		printf("Averagetime = %ld\n", averagetime );
	
}
