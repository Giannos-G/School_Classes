/*@ begin PerfTuning (
 def build {
  arg build_command = 'gcc -O0';
 }
 def performance_counter {
  arg method = 'basic timer';
  arg repetitions = 10;
 }
 def performance_params {
  param UF[] = range(1,33);
 }

 def input_params {
  param N[] = [1000,10000000];
 }

 def input_vars {
  decl static double y[N] = random;
  decl double a1 = random;
  decl double a2 = random;
  decl double a3 = random;
  decl double a4 = random;
  decl static double x1[N] = random;
  decl static double x2[N] = random;
  decl static double x3[N] = random;
  decl static double x4[N] = random;
 }

 def search {
  arg algorithm = 'Simplex';
  arg time_limit = 10;
  arg total_runs = 10;
  arg simplex_local_distance =2;
  arg simplex_reflection_coef =1.5;
  arg simplex_expansion_coef = 2.5;
  arg simplex_contraction_coef = 0.6;
  arg simplex_shrinkage_coef = 0.7;
 }
) @*/
if ((N<=1000)) {

/**-- (Generated by Orio) 
Best performance cost: 
  [4.801e-06, 4.113e-06, 3.881e-06, 3.884e-06, 3.883e-06, 3.838e-06, 3.867e-06, 3.842e-06, 3.848e-06, 3.859e-06] 
Tuned for specific problem sizes: 
  N = 1000 
Best performance parameters: 
  UF = 3 
--**/


int i;

/*@ begin Loop ( 
    transform Unroll(ufactor=UF) 
    for (i=0; i<=N-1; i++)
   y[i] = y[i] + a1*x1[i] + a2*x2[i] + a3*x3[i];
) @*/
for (int loop_loop_45=0; loop_loop_45 < 1; loop_loop_45++)  {
    int i;
    for (i = 0; i <= N - 3; i = i + 3) {
      y[i] = y[i] + a1 * x1[i] + a2 * x2[i] + a3 * x3[i];
      y[(i + 1)] = y[(i + 1)] + a1 * x1[(i + 1)] + a2 * x2[(i + 1)] + a3 * x3[(i + 1)];
      y[(i + 2)] = y[(i + 2)] + a1 * x1[(i + 2)] + a2 * x2[(i + 2)] + a3 * x3[(i + 2)];
    }
    for (i = N - ((N - (0)) % 3); i <= N - 1; i = i + 1) 
      y[i] = y[i] + a1 * x1[i] + a2 * x2[i] + a3 * x3[i];
  }
/*@ end @*/

} else if ((N<=10000000)) {

/**-- (Generated by Orio) 
Best performance cost: 
  [0.0352469, 0.0355375, 0.0350997, 0.0353247, 0.0464306, 0.0372423, 0.0370863, 0.0378453, 0.0394467, 0.0410393] 
Tuned for specific problem sizes: 
  N = 10000000 
Best performance parameters: 
  UF = 11 
--**/


int i;

/*@ begin Loop ( 
    transform Unroll(ufactor=UF) 
    for (i=0; i<=N-1; i++)
   y[i] = y[i] + a1*x1[i] + a2*x2[i] + a3*x3[i];
) @*/
for (int loop_loop_45=0; loop_loop_45 < 1; loop_loop_45++)  {
    int i;
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
  }
/*@ end @*/

}
/*@ end @*/
