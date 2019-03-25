#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>

using namespace std;

int main(){
    int n,i,j,k,p;
    float a[5][5],b[5],x[5],factor,pivot,sum,large,temp;
    printf("enter the size of the matrix:\n");
    scanf("%d",&n);
    printf("enter the coefficent of the matrix\n");
    for(i=1;i<=n;i++)
    {
                    for(j=1;j<=n;j++)
                    {
                    scanf("%f",&a[i][j]);
                    }
    }
    printf("enter the vector matrix of linear system\n");
    for(i=1;i<=n;i++)
    {
    scanf("%f",&b[i]);
    }
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
        getch();
    return 0;
}