//lucas kermessi - es98872
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

int pow2(double n){ // funcao para descobrir a potencia de 2 adequada
    double l = 0;
    int i = 0;
    bool achou = false;
    bool pow2 = false;
    int escolhido;

    l = log10(n)/log10(2);             // formula em log para descobrir se é potencia de 2, caso seja, o numero será inteiro

    if(fmod(l,1)==0){               // caso o resto entre o numero descoberto e 1, seja zero, logo é potencia de 2
        pow2 = true;
    }
    if(pow2 == true){
        escolhido = n;
    }
    else
    {
    while(achou == false && pow2 == false){        // loop para descobrir a potencia de 2 que se adequa para expandir a matriz
        double k = log10(i)/log10(2);
        if(fmod(k,1) == 0 && i > n){
            achou = true;
            escolhido = i;
        }
        i++; 
    }
    }
    return escolhido;
}
////////////////aLOCaÇÃO\\\\\\\\\\\\\\\\\\\\\\\\;

long int **alocaMatriz(long int **M, int n){
  int i;
 
  M = (long int **)malloc(sizeof(long int *)*n);
  if(M == NULL){
    printf("falta memoria.\n");
    exit(1);
  }
  for(i = 0; i < n; i++){
    M[i] = (long int *)malloc(sizeof(long int)*n);
    if(M[i] == NULL){
      printf("falta memoria.\n");
      exit(1);
    }
  }
  return M;
}

long int **desalocaMatriz(long int **M, int m){
  int i;
  for(i = 0; i < m; i++)
    free(M[i]);
  free(M);
  return(NULL);
}

//////////////////////\\\\\\\\\\\\\\\\\\\\\;

//gera valores randomicos para as matrizes, somente para testes
long int **randMatriz(int n, long int **M){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            M[i][j] = rand() % 10;
        }
    }
    return M;
}

// le as matrizes
long int **leMatriz(int n, long int **M){
    for(int i = 0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%ld",&M[i][j]);
        }
    }
    return M;
}

void subtMatriz(long int **A, long int **B,long int **C, int n){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            C[i][j] = A[i][j] - B[i][j]; 
        }
    }

}

void somaMatriz(long int **A, long int **B, long int **C, int n){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            C[i][j] = A[i][j] + B[i][j]; 
        }
    }
}
/* seria utilizada essa funcao para otimizar o algoritmo do caso base, mas o valgrind acusou muitos erros depois que eu implementei
void multPadrao(long int **A, long int **B, long int **C, int n){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            for(int k = 0;k<n;k++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}*/

void multMatriz(long int **A, long int **B, long int **C, int n) {

    if (n == 1){ // caso a matriz seja de ordem 1 basta multiplicar seus elementos, sendo este o caso base da funcao recursiva
        C[0][0] = A[0][0] * B[0][0];
    }
    else {
        long int **A11, **A12, **A21, **A22, **B11, **B12, **B21, **B22, **C11, **C12, **C21, **C22;
        // matrizes para o calculo de c11, c12, c21 e c22
        long int **M1, **M2, **M3, **M4, **M5, **M6, **M7;

        int tamanhoN = (n/2); // como as matrizes se dividem em 4, a ordem divide em 2

        A11 = alocaMatriz(A11, tamanhoN);
        A12 = alocaMatriz(A12, tamanhoN);
        A21 = alocaMatriz(A21, tamanhoN);
        A22 = alocaMatriz(A22, tamanhoN);

        B11 = alocaMatriz(B11, tamanhoN);
        B12 = alocaMatriz(B12, tamanhoN);
        B21 = alocaMatriz(B21, tamanhoN);
        B22 = alocaMatriz(B22, tamanhoN);

        //particionando a matriz em 4 pedaços de ordem n/2
        for (int i=0;i<tamanhoN;i++) {
            for (int j=0;j<tamanhoN;j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j+tamanhoN];
                A21[i][j] = A[i+tamanhoN][j];
                A22[i][j] = A[i+tamanhoN][j+tamanhoN];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j+tamanhoN];
                B21[i][j] = B[i+tamanhoN][j];
                B22[i][j] = B[i+tamanhoN][j+tamanhoN];
            }
        }

        C11 = alocaMatriz(C11, tamanhoN);
        C12 = alocaMatriz(C12, tamanhoN);
        C21 = alocaMatriz(C21, tamanhoN);
        C22 = alocaMatriz(C22, tamanhoN);

        M1 = alocaMatriz(M1, tamanhoN);
        M2 = alocaMatriz(M2, tamanhoN);
        M3 = alocaMatriz(M3, tamanhoN);
        M4 = alocaMatriz(M4, tamanhoN);
        M5 = alocaMatriz(M5, tamanhoN);
        M6 = alocaMatriz(M6, tamanhoN);
        M7 = alocaMatriz(M7, tamanhoN);

        //matrizes auxilizares para o calculo das matrizes M.
        long int **aux1 = alocaMatriz(aux1, tamanhoN);
        long int **aux2 = alocaMatriz(aux2, tamanhoN);
        // calculo das matrizes que darão origem a M1, M2, M3, M4, M5, M6 E M7 utilizadas para o calculo das subM C
        // utiliza-se recursividade nesse ponto, pois chama a função da multiplicação varias vezes ate obter algo de ordem 1
        // e agrupar posteriormente obtendo a matriz "resultado"
        somaMatriz(A11, A22, aux1, tamanhoN);
        somaMatriz(B11, B22, aux2, tamanhoN);
        multMatriz(aux1, aux2, M1, tamanhoN); // M1 = (A 1,1 + A 2,2 )(B 1,1 + B 2,2 )

        somaMatriz(A21, A22, aux1, tamanhoN);
        multMatriz(aux1, B11, M2, tamanhoN); // M2 = (A 2,1 + A 2,2 )B 1,1

        subtMatriz(B12, B22, aux2, tamanhoN);
        multMatriz(A11, aux2, M3, tamanhoN); // M3 = A 1,1 (B 1,2 − B 2,2 )

        subtMatriz(B21, B11, aux2, tamanhoN);
        multMatriz(A22, aux2, M4, tamanhoN); // M4 = A 2,2 (B 2,1 − B 1,1 )

        somaMatriz(A11, A12, aux1, tamanhoN);
        multMatriz(aux1, B22, M5, tamanhoN); // M5 = (A 1,1 + A 1,2 )B 2,2	

        subtMatriz(A21, A11, aux1, tamanhoN);
        somaMatriz(B11, B12, aux2, tamanhoN);
        multMatriz(aux1, aux2, M6, tamanhoN); // M7 = (A 2,1 − A 1,1 )(B 1,1 + B 1,2 )

        subtMatriz(A12, A22, aux1, tamanhoN);
        somaMatriz(B21, B22, aux2, tamanhoN);
        multMatriz(aux1, aux2, M7, tamanhoN);// M7 = (A 1,2 − A 2,2 )(B 2,1 + B 2,2 )

        //Submatrizes do resultado 

        somaMatriz(M1, M4, aux1, tamanhoN);
        somaMatriz(aux1, M7, aux2, tamanhoN);
        subtMatriz(aux2, M5, C11, tamanhoN); // calculo de C11 M 1 + M 4 − M 5 + M 7

        somaMatriz(M3, M5, C12, tamanhoN); // calculo de C12 M 3 + M 5

        somaMatriz(M2, M4, C21, tamanhoN); // calculo de C21 M 2 + M 4  

        somaMatriz(M1, M3, aux1, tamanhoN);
        somaMatriz(aux1, M6, aux2, tamanhoN);
        subtMatriz(aux2, M2, C22, tamanhoN); // calculo de C22 M 1 − M 2 + M 3 + M 6

        //fazer o contrario do ultimo for, nesse caso, agrupar os 4 blocos da matriz C
        for (int i= 0;i<tamanhoN;i++) {
            for (int j=0;j<tamanhoN;j++) {
                C[i][j] = C11[i][j];
                C[i][j+tamanhoN] = C12[i][j];
                C[i+tamanhoN][j] = C21[i][j];
                C[i+tamanhoN][j+tamanhoN] = C22[i][j];
            }
        }
//libera AS MATRIZES ALOCADAS DURANTE A FUNÇÃO
        A11 = desalocaMatriz(A11, tamanhoN);
        A12 = desalocaMatriz(A12, tamanhoN);
        A21 = desalocaMatriz(A21, tamanhoN);
        A22 = desalocaMatriz(A22, tamanhoN);
        B11 = desalocaMatriz(B11, tamanhoN);
        B12 = desalocaMatriz(B12, tamanhoN);
        B21 = desalocaMatriz(B21, tamanhoN);
        B22 = desalocaMatriz(B22, tamanhoN);
        C11 = desalocaMatriz(C11, tamanhoN);
        C12 = desalocaMatriz(C12, tamanhoN);
        C21 = desalocaMatriz(C21, tamanhoN);
        C22 = desalocaMatriz(C22, tamanhoN);
        M1 = desalocaMatriz(M1, tamanhoN);
        M2 = desalocaMatriz(M2, tamanhoN);
        M3 = desalocaMatriz(M3, tamanhoN);
        M4 = desalocaMatriz(M4, tamanhoN);
        M5 = desalocaMatriz(M5, tamanhoN);
        M6 = desalocaMatriz(M6, tamanhoN);
        M7 = desalocaMatriz(M7, tamanhoN);
        aux1 = desalocaMatriz(aux1, tamanhoN);
        aux2 = desalocaMatriz(aux2, tamanhoN);
    }

}

// printa as matrizes
void printMatriz(int n, long int **M){
    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%ld ",M[i][j]);
        }
        printf("\n");
    }
}

// zera as matrizes A, B e C
void zeraMatriz(int n, long int **A, long int **B, long int **C){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            A[i][j] = 0;
            B[i][j] = 0;
            C[i][j] = 0;
        }
    }

}
int main(){
    srand(time(NULL));

    int newN;

    long int **A, **B;
    long int **C;
    double n;
    scanf("%lf",&n);
    newN = pow2(n);

    A = alocaMatriz(A, newN);
    B = alocaMatriz(B, newN);
    C = alocaMatriz(C, newN);

    zeraMatriz(newN, A, B, C);

    //A = randMatriz(n,A);
    //B = randMatriz(n,B);

    A = leMatriz(n,A);
    B = leMatriz(n,B);

    multMatriz(A,B,C,newN);

    //printMatriz(n,A);
    //printMatriz(n,B);
    printMatriz(n,C);
    //printMatriz(n,B);


    desalocaMatriz(A,newN);
    desalocaMatriz(B,newN);
    desalocaMatriz(C,newN);
    
    return 0;
}