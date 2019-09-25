#include <stdio.h>
#include <stdlib.h>

int main(){

    int n;
    scanf("%d",&n);

    long int A[n][n];
    long int B[n][n];
    long int C[n][n];

//Leitura da matriz A
    for(int l =0;l<n;l++){
        for(int k=0;k<n;k++){
            scanf("%ld",&A[l][k]);
        }
    }
//Leitura da matriz B
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            scanf("%ld",&B[i][j]);
        }
    }
//Zeramento da matriz C
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            C[i][j] = 0;
        }
    }
//multiplicação dos elementos das matrizes
     for(int i = 0 ; i < n; i++)
        for(int j = 0; j < n; j++)
           for(int k = 0; k < n; k++)
            C[i][j] = C[i][j] + A[i][k] * B[k][j]; // consiste na multiplicação de cada elemento e depois na soma com a proxima
                                                   //multiplicação entre os outros elementos

//printar na tela o resultado
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            printf("%ld ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}