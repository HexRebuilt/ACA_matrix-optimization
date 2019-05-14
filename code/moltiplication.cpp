#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <omp.h>

using namespace std;


//#define THREADNUMB 1

#define MAXNUMBER 10
#define MINNUMBER 0
 
void showMatrix(float **matrix, int size){
    cout << "\n";
    for(int i=0; i <size;i++ ){
        for(int j=0; j< size; j++){
            cout << matrix[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
}

void create_Matrix (float **random, int size){
    
    int i, j;
    int range = MAXNUMBER - MINNUMBER;
    srand(static_cast<unsigned>(time(0))); 
    //srand(time(NULL));
    //#pragma omp parallel for 
        for(i = 0; i <size; i++)
            for(j = 0; j< size; j++)
                random[i][j] = rand() %(range);

}

void multiply(float **a, float **b, float **r, int size){
    //the program will work only on square matrices
    //multiply a*b
    #pragma omp parallel for collapse(3)
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                for(int k = 0; k < size; k++)
                    r[i][j] = r[i][j] + a[i][k]*b[k][j];
    //showMatrix(results);
}

int main(int argc,char **argv){
    // the first arg is the size of the matrix and the second one is the thread number
    int size = atoi(argv[1]);
    omp_set_num_threads(atoi(argv[2]));

    int i,j;
	//float a[size][size], b[size][size], at[size][size], bt[size][size];
    float **a = (float **)malloc(size * sizeof(float*));
    float **b = (float **)malloc(size * sizeof(float*));
    float **r = (float **)malloc(size * sizeof(float*));
    
    #pragma omp parallel for
    for(int i = 0; i < size; i++){
        a[i] = (float *)malloc(size * sizeof(float));
        b[i] = (float *)malloc(size * sizeof(float));
        r[i] = (float *)malloc(size * sizeof(float));
    }
    #pragma omp parallel for collapse(2)
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                r[i][j] = 0;
    
    
    create_Matrix(a, size);
    //cout << "\nMatrix A:\n";
    //showMatrix(a);
    create_Matrix(b, size);
    //cout << "\nMatrix B:\n";
    //showMatrix(b);
    cout << "\n\nA * B =\n";
    double time= omp_get_wtime();
    multiply(a,b,r, size);
    time = omp_get_wtime()-time;
    cout << "\nExecution time: "<< time;
    getch();
    free(a);
    free(b);
    free(r);
    return 0;
}