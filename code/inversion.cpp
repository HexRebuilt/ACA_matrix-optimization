#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>

using namespace std;
#define SIZE 10
#define MAXNUMBER 90
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
    float results[SIZE][SIZE];

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


//---------------------------------------------------
//	calculate minor of matrix OR build new matrix : k-had = minor
void minor(float b[SIZE][SIZE],float a[SIZE][SIZE],int i,int n){
	int j,l,h=0,k=0;
	for(l=1;l<n;l++)
		for( j=0;j<n;j++){
			if(j == i)
				continue;
			b[h][k] = a[l][j];
			k++;
			if(k == (n-1)){
				h++;
				k=0;
			}
		}
}// end function

//---------------------------------------------------
//	calculate determinte of matrix
float det(float a[SIZE][SIZE],int n){
	int i;
	float b[SIZE][SIZE],sum=0;
	if (n == 1)
    return a[0][0];
	else if(n == 2)
    return (a[0][0]*a[1][1]-a[0][1]*a[1][0]);
	else
		for(i=0;i<n;i++){
			minor(b,a,i,n);	// read function
			sum = (float) (sum+a[0][i]*pow(-1,i)*det(b,(n-1)));	// read function	// sum = determinte matrix
		}
    return sum;
}// end function

//---------------------------------------------------
//	calculate transpose of matrix
void transpose(float c[SIZE][SIZE],float d[SIZE][SIZE],int n,float det){
	int i,j;
	float b[SIZE][SIZE];
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			b[i][j] = c[j][i];
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			d[i][j] = b[i][j]/det;	// array d[][] = inverse matrix
}// end function

//---------------------------------------------------
//	calculate cofactor of matrix
void cofactor(float a[SIZE][SIZE],float d[SIZE][SIZE],int n,float determinte){
	float b[SIZE][SIZE],c[SIZE][SIZE];
	int l,h,m,k,i,j;
	for (h=0;h<n;h++)
		for (l=0;l<n;l++){
			m=0;
			k=0;
			for (i=0;i<n;i++)
				for (j=0;j<n;j++)
					if (i != h && j != l){
						b[m][k]=a[i][j];
						if (k<(n-2))
							k++;
						else{
							k=0;
							m++;
						}
					}
			c[h][l] = (float) pow(-1,(h+l))*det(b,(n-1));	// c = cofactor Matrix
		}
	transpose(c,d,n,determinte);	// read function
}// end function

//---------------------------------------------------
//	calculate inverse of matrix
void inverse(float a[SIZE][SIZE],float d[SIZE][SIZE],int n,float det){
	if(det == 0)
		cout<<"\nInverse of Entered Matrix is not possible\n";
	else if(n == 1)
		d[0][0] = 1;
	else
		cofactor(a,d,n,det);	// read function
}// end function

//---------------------------------------------------
//main fuction exe
int main(void){
	int i,j,n = SIZE;
	float a[SIZE][SIZE], b[SIZE][SIZE], at[SIZE][SIZE], bt[SIZE][SIZE], deterA, deterB;
	create_Matrix(a,1);
    cout << "\nMatrix A:\n";
    showMatrix(a);
    deterA = (float) det(a,n);	// read function
    cout<<"\n\nDeterminant of the Matrix A: "<<deterA;
    
    create_Matrix(b,2);
    cout << "\nMatrix B:\n";
    showMatrix(b);
    deterB = (float) det(b,n);	// read function
    cout<<"\n\nDeterminant of the Matrix B: "<<deterB;

    cout<< "\n\nA * B =\n";
    multiply(a,b);


    cout<<"\n\nInversion of the Matrix A: ";
	if(deterA != 0){
	    inverse(a,at,n,deterA);	// read function
	    showMatrix(at);
    }
    else{
        cout<<"\nInverse of Entered Matrix is not possible\n";
    }
    
    cout<<"\n\nInversion of the Matrix B: ";
    if(deterB != 0){
	    inverse(b,bt,n,deterB);	// read function
	    showMatrix(bt);
    }
    else{
        cout<<"\nInverse of Entered Matrix is not possible\n";
    }

    /*cout << "\n\nVerify A': A * A' = I";
    multiply(a,at);

    cout << "\n\nVerify B': B * B' = I";
    multiply(b,bt);
    */
    
    return 0;
}