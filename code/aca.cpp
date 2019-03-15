#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>
using namespace std;

#define SIZE 2
 
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

double** create_Matrix ()
{
    double** random = new double*[SIZE];
    for (int i=0; i< SIZE; i++){
        random[i] = new double [SIZE];
    }

    int i, j;
    int max = 100, min = 0, range = max-min;
    srand(time(NULL)); 

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

double determinant( double** matrix, int n) {   
   double det = 0;
   double** submatrix = new double*[n];
    for (int i=0; i< n; i++){
        submatrix[i] = new double [n];
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; i < n; i++)
            submatrix[i][j] = 0;

    for (int x = 0; x < n; x++) {
        int subi = 0; 
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x)
                continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
    }
   return det;
}

void matrixInversion(double** matrix){
    double** a = new double*[SIZE];
    for (int i=0; i< SIZE; i++){
        a[i] = new double [SIZE];
    }
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; i < SIZE; i++)
            a[i][j] = 0;
    
    double det = determinant(matrix,SIZE);

}


int main(){
    // creations of the 2 random matrices 
    double** matrixA = create_Matrix();
    double** matrixB = create_Matrix();

    cout << "\nMatrix A:";
    showMatrix(matrixA);
    cout << "\nMatrix B";
    showMatrix(matrixB);
    
    cout << "\nA*B";
    multiply(matrixA,matrixB);
    
    cout << "det:A\n";
    cout << determinant(matrixA,SIZE);
    /*
    cout << "\nInversion matrix A";
    matrixInversion(matrixA);

    cout << "\nInversion matrix B";
    matrixInversion(matrixB);
    */
    return 0;
}
