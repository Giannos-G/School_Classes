/*Parallel Hierarchical One-Dimensional Search for motion estimation*/
/*Initial algorithm - Used for simulation and profiling             */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


#define N 144     /*Frame dimension for QCIF format*/
#define M 176     /*Frame dimension for QCIF format*/
//#define B 8      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                    original location of the block.*/

int Bx, By = 0;

unsigned long long timetobesent = 0; // Used for timetobesentfunct()


void read_sequence(int current[N][M], int previous[N][M])
{ 
	FILE *picture0, *picture1;
	int i, j;

	if((picture0=fopen("akiyo0.y","rb")) == NULL)
	{
		printf("Previous frame doesn't exist.\n");
		exit(-1);
	}

	if((picture1=fopen("akiyo1.y","rb")) == NULL) 
	{
		printf("Current frame doesn't exist.\n");
		exit(-1);
	}

  /*Input for the previous frame*/
  for(i=0; i<N; i++)
  {
    for(j=0; j<M; j++)
    {
      previous[i][j] = fgetc(picture0);
    }
  }

	/*Input for the current frame*/
	for(i=0; i<N; i++)
  {
		for(j=0; j<M; j++)
    {
			current[i][j] = fgetc(picture1);
    }
  }

	fclose(picture0);
	fclose(picture1);
}


void phods_motion_estimation(int current[N][M], int previous[N][M],
    int vectors_x[N/Bx][M/By],int vectors_y[N/Bx][M/By])
{
  int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;
  //////////////////////////
  // Time computation
  struct timeval begin,end;
  begin.tv_usec = 0;
  begin.tv_sec =0;
  end.tv_usec = 0;
  end.tv_sec=0;
  gettimeofday (&begin, NULL);
  /////////////////////////// 
  distx = 0;
  disty = 0;

  /*Initialize the vector motion matrices*/
  for(i=0; i<N/Bx; i++)           // Loop Interchange did not work 
  {
    for(j=0; j<M/By; j++)       
    {
      vectors_x[i][j] = 0;
      vectors_y[i][j] = 0;
     
    }
  }

  /*For all blocks in the current frame*/
  for(x=0; x<N/Bx; x++) //Loop blocking did not work 
  {
    for(y=0; y<M/By; y++) //Loop blocking did not work 
    {
      S = 4;
      while(S > 0)
      {
        min1 = 255*Bx*By;
        min2 = 255*Bx*By;
         int __vectors_x__ = vectors_x[x][y];
        /*For all candidate blocks in both dimensions*/
        for(i=-S; i<S+1; i+=S)     
        {
          distx = 0;
          disty = 0;
         
          /*For all pixels in the block*/
          for(k=0; k<Bx; k++)   
          {
            for(l=0; l<By; l++) 
            {
                  p1 = current[Bx*x+k][By*y+l];

                  if((Bx*x + __vectors_x__  + i + k) < 0 ||
                  (Bx*x + __vectors_x__  + i + k) > (N-1) ||
                  (By*y + __vectors_x__  + l) < 0 ||
                  (By*y + __vectors_x__  + l) > (M-1))
                  {
                  p2 = 0;
                  } else {
                  p2 = previous[Bx*x+__vectors_x__+i+k][By*y+__vectors_x__ +l];
                  }
                distx += abs(p1-p2);
                ///////////////////////////////////////////////////////////////////

                if((Bx*x + __vectors_x__  + k) <0 ||
                    (Bx*x + __vectors_x__  + k) > (N-1) ||
                    (By*y + __vectors_x__  + i + l) < 0 ||
                    (By*y + __vectors_x__  + i + l) > (M-1))
                {
                  q2 = 0;
                } else {
                  q2 = previous[Bx*x+__vectors_x__ +k][By*y+__vectors_x__ +i+l];
                }
                  disty += abs(p1-q2);
            }
          }

          if(distx < min1)
          {
            min1 = distx;
            bestx = i;
          }

          if(disty < min2)
          {
            min2 = disty;
            besty = i;
          }

        }
        S = S/2;
        __vectors_x__  += bestx;
        __vectors_x__  += besty;
      }
    
    }
  } 
  //////////////////////////
  //Time computation
  gettimeofday(&end, NULL);
  unsigned long long t = end.tv_sec * 1000000ULL + end.tv_usec - begin.tv_sec * 1000000ULL - begin.tv_usec;
  printf(" Runtime: %lld us \n", t);
  timetobesent = t;  // To be used from timetobesentfunct()
  //////////////////////////
} 

unsigned long long timetobesentfunct(){
  return timetobesent;
}

int mainexecutable()
{ 
  int current[N][M], previous[N][M], motion_vectors_x[N/Bx][M/By],
  motion_vectors_y[N/Bx][M/By], i, j;
	read_sequence(current,previous);
  	phods_motion_estimation(current,previous,motion_vectors_x,motion_vectors_y);
  return 0;
}
