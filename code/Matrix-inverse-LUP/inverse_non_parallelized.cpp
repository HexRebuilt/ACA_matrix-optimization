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
 
void showMatrix(float **matrix){
    cout << "\n";
    for(int i=0; i <SIZE;i++ ){
        for(int j=0; j< SIZE; j++){
            cout << matrix[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
}

void create_Matrix (float **random,int number){
    
    int i, j;
    int range = MAXNUMBER - MINNUMBER;
    srand(static_cast<unsigned>(time(0))+number); 
    //srand(time(NULL));
    #pragma omp parallel for collapse(2)
        for(i = 0; i <SIZE; i++)
            for(j = 0; j< SIZE; j++)
                random[i][j] = rand() %(range);
}

void lu(float **a, float **l, float **u){
    int i = 0, j = 0, k = 0;
    
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            if (j < i)
                l[j][i] = 0;
            else{
                l[j][i] = a[j][i];
                for (k = 0; k < i; k++){
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }

        for (j = 0; j < SIZE; j++){
            if (j < i)
                u[i][j] = 0;
            else if (j == i)
                u[i][j] = 1;
            else
            {
                u[i][j] = a[i][j] / l[i][i];
                for (k = 0; k < i; k++)
                {
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }
            }
        }
    }
}

void pivoting(float **a, float **p){
    for (int k = 0; k < SIZE-1; k++)
    {   int imax = 0;
        //foreach column i need to find which row has the maximum (in module) value
        for (int j = k; j < SIZE; j++)
        {
            //finding the maximum
            if (abs(a[j][k]) > abs(a[imax][k])){
                imax = j;
            }
        }
        //now i swap the rowa imax and k
    
    }


    
}

int main(void){
    int i,j;
	float **a = (float **)malloc(SIZE * sizeof(float*));
    float **l = (float **)malloc(SIZE * sizeof(float*));
    float **u = (float **)malloc(SIZE * sizeof(float*));
    float **p = (float **)malloc(SIZE * sizeof(float*));
    
    for(int i = 0; i < SIZE; i++){
        a[i] = (float *)malloc(SIZE * sizeof(float));
        l[i] = (float *)malloc(SIZE * sizeof(float));
        u[i] = (float *)malloc(SIZE * sizeof(float));
        p[i] = (float *)malloc(SIZE * sizeof(float));
    }
    // create the identity pivot matrix
    #pragma omp parallel for collapse(2)
        for(int i = 0; i < SIZE; i++)
            for(int j = 0; j < SIZE; j++)
                p[i][j] = 0;
    #pragma omp parallel
        for(int i = 0; i < SIZE; i++)
            p[i][i] = 1;
    
    
    create_Matrix(a,1);
    //cout << "\nMatrix A:\n";
    //showMatrix(b);
    double time= omp_get_wtime();
    
    /**P*a = l*u and LUx =p
    where p is the column to pivot of the b matrix and x is a column of the inverse
    
    */
    //i pivot a and p before the inversion
    pivoting(a,b);
    lu(a,l,u);
     
    
    //cout << "\nL matrix:\n";
    //showMatrix(l);
    //cout << "\nU matrix:\n";
    //showMatrix(u);


    /**P*a = l*u and LUx =p
    where p is the column to pivot of the b matrix and x is a column of the inverse
    
    */




    time = omp_get_wtime()-time;
    cout << "\nExecution time: "<< time;
    getch();
    return 0;
}