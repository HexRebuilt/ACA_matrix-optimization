#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <omp.h>

using namespace std;
#define SIZE 4
#define MAXNUMBER 10
#define MINNUMBER 0
 
void showMatrix(float matrix[SIZE][SIZE]){
    cout << "\n";
    for(int i=0; i <SIZE;i++ ){
        for(int j=0; j< SIZE; j++){
            cout << matrix[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
}

void create_Matrix (float random[SIZE][SIZE],int number){
    
    int i, j;
    int range = MAXNUMBER - MINNUMBER;
    srand(static_cast<unsigned>(time(0))+number); 
    //srand(time(NULL));
    
    for(i = 0; i <SIZE; i++)
        for(j = 0; j< SIZE; j++)
            random[i][j] = rand() %(range);
}

void multiply(float a[SIZE][SIZE], float b[SIZE][SIZE]){
    //the program will work only on square matrices
    float results[SIZE][SIZE]={0};

    //multiply a*b
        for(int i = 0; i < SIZE; i++)
            for(int j = 0; j < SIZE; j++)
                for(int k = 0; k < SIZE; k++)
                    results[i][j] = results[i][j] + a[i][k]*b[k][j];
    
    showMatrix(results);
}

int main(void){
    double time= omp_get_wtime();
	int i,j,n = SIZE;
	float a[SIZE][SIZE], b[SIZE][SIZE], at[SIZE][SIZE], bt[SIZE][SIZE], deterA, deterB;
	create_Matrix(a,1);
    cout << "\nMatrix A:\n";
    showMatrix(a);
    create_Matrix(b,2);
    cout << "\nMatrix B:\n";
    showMatrix(b);
    
    cout<< "\n\nA * B =\n";
    multiply(a,b);
    time = omp_get_wtime()-time;
    cout << "\nExecution time: "<< time;
    return 0;
}