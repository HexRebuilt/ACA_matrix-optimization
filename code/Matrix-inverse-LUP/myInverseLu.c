# include <stdio.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <omp.h>

# define	SIZE	2000

int main(){
    double time = omp_get_wtime();

    float **A = (float **)malloc((SIZE) * sizeof(float*));
    float **A1 = (float **)malloc((SIZE) * sizeof(float*));
    float **I = (float **)malloc((SIZE+) * sizeof(float*));
    float **L = (float **)malloc((SIZE) * sizeof(float*));
    float **U = (float **)malloc((SIZE) * sizeof(float*));
    
    #pragma omp parallel for
      for(int i = 0; i < (SIZE); i++){
          A[i] = (float *)malloc((SIZE) * sizeof(float));
          A1[i] = (float *)malloc((SIZE) * sizeof(float));
          I[i] = (float *)malloc((SIZE) * sizeof(float));
      }

      for(int i = 0; i < (SIZE); i++){
      
      }


    /* Its i-th row shows the position of '0' in the i-th row of the pivot that is used
    * when performing the LUP decomposition of A. The rest of the elements in that row of
    * the pivot would be zero. In this program, we call this array 'P' a 'permutation'. */
    int *P= (int *)malloc((SIZE) * sizeof(int));

    //float B[SIZE][SIZE], X[SIZE], Y[SIZE]; //Temporaty spaces.
    float **B = (float **)malloc((SIZE) * sizeof(float*));
    float *X = (float *)malloc((SIZE) * sizeof(float*));
    float *Y = (float *)malloc((SIZE) * sizeof(float*));
  
  #pragma omp parallel for  
    for(int i = 0; i < (SIZE); i++)
        B[i] = (float *)malloc((SIZE) * sizeof(float));

    #pragma omp parallel for collapse(2)
    for(int i = 0; i <= SIZE; i++) 
        for(int j = 0; j <= SIZE; j++)
        A[i][j] = A1[i][j] = sin(i*j*j+i)*2;

  //double time = omp_get_wtime();



    time = omp_get_wtime()-time;
    printf('\nExecution time: %f\n', time);
  return 0;
}