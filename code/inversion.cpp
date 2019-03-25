#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>

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

void lu(float a[SIZE][SIZE], float l[SIZE][SIZE], float u[SIZE][SIZE], int n){

    int i = 0, j = 0, k = 0;

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (j < i)
                l[j][i] = 0;
            else{
                l[j][i] = a[j][i];
                for (k = 0; k < i; k++)
                {
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }
        for (j = 0; j < n; j++){
            if (j < i)
                u[i][j] = 0;
            else if (j == i)
                u[i][j] = 1;
            else{
                u[i][j] = a[i][j] / l[i][i];
                for (k = 0; k < i; k++)                {
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }
            }
        }
    }
}

int findImax(float a[SIZE][SIZE], int column){
    int imax=column;
	for(int i = column; i < SIZE; i++)
	{
		if (a[i][column]>a[imax][column]) {
			imax=i;
			cout<<"\n i max:"<<imax;
		}
	}
    return imax;
}

void swapRows(float a[SIZE][SIZE], float ap[SIZE][SIZE], float b[SIZE][SIZE], int imax, int column){
    //swappo le righe per il primo passaggio
	for (int k =0; k < SIZE; k++){
		ap[column][k] = a[imax][k];
		ap[imax][k] = a[column][k];
		float tmp = b[imax][k];
		b[imax][k] = b[column][k];
        b[column][k] = tmp;
	}
}

void triangularize(float a[SIZE][SIZE], float b[SIZE][SIZE],int row){
    float number;
    for(int j = 0; j < SIZE; j++)
    {
        
    }
    


}

void pivoting(float a[SIZE][SIZE],float ap[SIZE][SIZE],float b[SIZE][SIZE]){
	for(int i = 0; i < SIZE; i++){
        int imax = findImax(a,i);
        //cout <<"\nbefore row inversion a:";
        //showMatrix(a);
        cout <<"\nafter inversion ap: ";
        //showMatrix(ap);
        //swapRows(a,ap,b,imax,i);
        if(i > 0){
            triangularize(a,b,i);
        }

    }
	
}

void luInversion(float a[SIZE][SIZE]){
    float l[SIZE][SIZE], u[SIZE][SIZE], y[SIZE][SIZE], x[SIZE][SIZE];
    int i = 0, j = 0;
    lu(a, l, u, SIZE); //it modifies the L matrix in order to be lower triangular and the U to be upper tri
  
    float b[SIZE][SIZE]= {0};
    for (int i = 0; i < SIZE; i++){
        b[i][i] = 1; //creating the identity matrix
    } 
	float ap [SIZE][SIZE];
	for(int i = 0; i< SIZE; i++)
		for(int j=0; j< SIZE; j++)
			ap[i][j] = a[i][j];

	pivoting(a,ap,b);
}

/*
void lu_decomposition(float a[SIZE][SIZE], b[SIZE][SIZE]){
    int n = SIZE,i,j,k,p;
    float x[SIZE],factor,pivot,sum,large,temp;
    
    printf("performing the forwar elimination....................\n");
    for(k=1;k<=n-1;k++)
    {
                    p=k;
                    large=abs(a[k][k]);
                    for(i=k+1;i<=n;i++)
                    {
                    if(abs(a[i][k])>large)
                                    {
                                    large=abs(a[i][k]);
                                    p=i;
                                    }
                    }
                    if(p!=k)
                    {
                                    for(j=k;j<=n;j++)
                                    {
                                    temp=a[p][i];
                                    a[p][j]=a[k][j];
                                    a[k][j]=temp;
                                    temp=b[p];
                                    b[p]=b[k];
                                    b[k]=temp;
                                    }
                    }

                    for(i=k+1;i<=n;i++)
                    {
                    factor=a[i][k]/a[k][k];
                                    for(j=1;j<=n;j++)
                                    {
                                    a[i][j]=a[i][j]-factor*a[k][j];
                                    }
                    b[i]=b[i]-factor*b[k];
                    }
    }
        printf("performing the bacward substitution\n");
        x[n]=b[n]/a[n][n];
        for(k=n-1;k>=1;k--)
        {
        sum=0.00;
        for(j=k+1;j<=n;j++)
        {
        sum=sum+a[k][j]*x[j];
        }
        x[k]=(b[k]-sum)/a[k][k];
        }
        printf("the values are:\n");
        for(i=1;i<=n;i++)
        {
        printf("%f\t",x[i]);
        }
}
*/


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

/*
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
*/
    cout << "\n\nVerify LU method";
    luInversion(a);

    
    return 0;
}