#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <omp.h>

using namespace std;
#define SIZE 5
#define MAXNUMBER 50
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
    for (int k = 0; k < SIZE-1; k++){   
        int imax = 0;
        //foreach column i need to find which row has the maximum (in module) value
        for (int j = k; j < SIZE; j++)
        {
            //finding the maximum
            if (abs(a[j][k]) > abs(a[imax][k])){
                imax = j;
                //cout <<"\nNew iMax = " << imax;
            }
        }
        //now i swap the row imax and k
        //cout <<"\nSwapping row "<<k << "and "<< imax;
        swap(a[k],a[imax]);
        swap(p[k],p[imax]);
    }


    
}

void forwardSubst(float **l, float **p, float *y, int column){
    /**
     * solving yi=Pi/ sum of Lrow-i
    */
    y[0]=p[0][column] /l[0][0];

    for(int i=0; i< SIZE; i++){
        y[i] = p[i][column];
        for (int j = 0; j < i; j++)
        {
            //the P[i] part has been done before
            y[i] = y[i] - l[i][j]*y[i-1] ;
        }
        y[i] = y[i]/l[i][i];
    }
}

void backwardSubst(float **u, float *y, float **a1, int column){
    /**
     * solving A^-1i=Pi/ sum of Lrow-i
    */
    a1[SIZE-1][column] = y[SIZE-1]/u[SIZE-1][SIZE-1];

    for(int i= SIZE-1; i >= 0; i--){
        y[i] = a1[i][column];
        for (int j = SIZE-1; j > i; j--)
        {   
            cout << "\ni ";
            cout << i;
            cout <<"\tj ";
            cout << j ;
            y[i] = y[i] - u[i][j]*y[i-1] ;
        }
        y[i] = y[i]/u[i][i];
    }
}

void findInverse(float **a, float **a1, float **l, float **u, float **p, float *yi){
    /**
     * foreach column i solve the system LUai=Pi with the i-th column
     * by using the forward substitution method
     * LYi=Pi
     * Uxi=Yi
     */

    //i can only parallelize this, so i can do each column indipendentily
    for(int i=0; i< SIZE; i++){
        float *y = (float *)malloc(SIZE * sizeof(float*));
        y = yi;
        forwardSubst(l,p,y,i);
        backwardSubst(u,y,a1,i);
    }

}

int main(void){
    int i,j;
	float **a = (float **)malloc(SIZE * sizeof(float*));
    float **l = (float **)malloc(SIZE * sizeof(float*));
    float **u = (float **)malloc(SIZE * sizeof(float*));
    float **p = (float **)malloc(SIZE * sizeof(float*));
    float **a1 = (float **)malloc(SIZE * sizeof(float*));
    float *y = (float *)malloc(SIZE * sizeof(float*)); 
    
    
    for(int i = 0; i < SIZE; i++){
        a[i] = (float *)malloc(SIZE * sizeof(float));
        a1[i] = (float *)malloc(SIZE * sizeof(float));
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
        for(int i = 0; i < SIZE; i++){
            p[i][i] = 1;
            y[i] =0;
        }
    
    
    create_Matrix(a,1);
    cout << "\nMatrix A:\n";
    showMatrix(a);
    //cout << "\nPivoting matrix:\n";
    //showMatrix(p);
    double time= omp_get_wtime();
    
    /**
     * P*a = l*u and LUx =p
     * where p is the column to pivot of the b matrix and x is a column of the inverse
    */
    //cout << "\nPivoting....\n";
    pivoting(a,p);

    /**cout << "\nMatrix A:\n";
    showMatrix(a);
    cout << "\nPivoting matrix:\n";
    showMatrix(p);
    */
    lu(a,l,u);
     
    /**
    cout << "\nL matrix:\n";
    showMatrix(l);
    cout << "\nU matrix:\n";
    showMatrix(u);
    */

   /**
    * solving the system LUxi=Pi where i is the column and x is the column
    * of the inverse to find
    */
    cout << "\nFinding the inverse...";
    findInverse(a,a1,l,u,p,y);
    
    cout<< "\nMatrix a^-1:\n";
    showMatrix(a1);

    time = omp_get_wtime()-time;
    cout << "\nExecution time: "<< time;
    getch();
    return 0;
}