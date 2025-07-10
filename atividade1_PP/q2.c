
#include <stdio.h> //habilita funções de entrada/saída como printf e scanf.
#include <stdlib.h> // habilita funções como rand() (número aleatório) e srand().
#include <time.h> // habilita a função time() para pegar a hora atual e variar os números aleatórios a cada execução.

#define N 4 // ordem da matriz 4×4.

// Função para gerar a matriz com números aleatórios entre 0 e 29
void gerarMatriz(int M[N][N]) {
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            M[i][j] = rand() % 30;
}

// Função para calcular a transposta da matriz M
void transpostaMatriz(int M[N][N], int MT[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            MT[j][i] = M[i][j]; // troca linha por coluna
}

// Função para multiplicar M × MT e guardar o resultado em R
void multiplicarMatrizes(int M[N][N], int MT[N][N], int R[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            R[i][j] = 0;
            for (int k = 0; k < N; k++)
                R[i][j] += M[i][k] * MT[k][j];
        }
}

// Verifica se a matriz resultado é a identidade
int ehOrtogonal(int R[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (i == j && R[i][j] != 1)
                return 0; // diagonal principal tem que ser 1
            else if (i != j && R[i][j] != 0)
                return 0; // fora da diagonal tem que ser 0
        }
    return 1;
}

// Função para imprimir a matriz
void imprimirMatriz(int M[N][N], const char* nome) {
    printf("\n%s:\n", nome);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d ", M[i][j]);
        printf("\n");
    }
}

int main() {
    int M[N][N], MT[N][N], R[N][N];

    gerarMatriz(M);
    transpostaMatriz(M, MT);
    multiplicarMatrizes(M, MT, R);

    imprimirMatriz(M, "Matriz Original");
    imprimirMatriz(MT, "Matriz Transposta");
    imprimirMatriz(R, "Matriz M x MT");

    if (ehOrtogonal(R))
        printf("\nMatriz Ortogonal\n");
    else
        printf("\nMatriz Nao Ortogonal\n");

    return 0;
}
