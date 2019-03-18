#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>
using namespace std;

#define SIZE 3
#define MAXNUMBER 5
#define MINNUMBER 0
 
void showMatrix(double** matrix){
    cout << "\n";
    for(int i=0; i <SIZE;i++ ){
        for(int j=0; j< SIZE; j++){
            cout << matrix[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
}

double** create_Matrix (int number){
    double** random = new double*[SIZE];
    for (int i=0; i< SIZE; i++){
        random[i] = new double [SIZE];
        //random[i] = 0;
    }

    int i, j;
    int range = MAXNUMBER - MINNUMBER;
    srand(static_cast<unsigned>(time(0))+number); 
    //srand(time(NULL));
    for(i = 0; i <SIZE; i++)
        for(j = 0; j< SIZE; j++)
            random[i][j] = rand() %(range);
    return random;
}

void multiply(double** a, double**b){
    //the program will work only on square matrices
    double** results = new double*[SIZE];
    for (int i=0; i< SIZE; i++){
        results[i] = new double [SIZE];
    }

    //initialize the matrix
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            results[i][j] = 0;
    
    //multiply a*b
        for(int i = 0; i < SIZE; i++)
            for(int j = 0; j < SIZE; j++)
                for(int k = 0; k < SIZE; k++)
                    results[i][j] = results[i][j] + a[i][k]*b[k][j];
    
    showMatrix(results);
}


int main(){
    // creations of the 2 random matrices 
    double** matrixA = create_Matrix(1);
    double** matrixB = create_Matrix(2);

    cout << "\nMatrix A:";
    showMatrix(matrixA);
    cout << "\nMatrix B";
    showMatrix(matrixB);
    
    cout << "\nA*B";
    multiply(matrixA,matrixB);
       
    return 0;
}
