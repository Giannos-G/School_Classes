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

int i;

/*@ begin Loop ( 
    transform Unroll(ufactor=UF) 
    for (i=0; i<=N-1; i++)
   y[i] = y[i] + a1*x1[i] + a2*x2[i] + a3*x3[i];
) @*/

/*@ end @*/

/*@ end @*/

