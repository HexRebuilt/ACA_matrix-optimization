
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4;


int main{

    // creations of the 2 random matrices 
    int[][] matrixA= create_Matrix();
    int[][] matrixB= create_Matrix();

    showMatrix(matrixA);
    showMatrix(matrixB);






    return 0;
}

void showMatrix(int[][] matrix){
    for(int i=0; i <SIZE;i++ ){
        for(int j=0; j< SIZE; j++){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int[][] create_Matrix ()
{
    int random[SIZE][SIZE];
    int i, j;

    srand(time(NULL));
    for(i = 0; i <SIZE; i++)
        for(j = 0; j< SIZE; j++)
            random[j][j] = rand();
    return random;
}