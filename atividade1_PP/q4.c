
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 30 // tamanho do vetor

// Função para preencher o vetor com números aleatórios de 1 a 30
void preencherVetor(int vetor[TAM]) {
    srand(time(NULL)); // inicializa gerador aleatório
    for (int i = 0; i < TAM; i++) {
        vetor[i] = (rand() % 30) + 1; // números entre 1 e 30
    }
}

// Função para ordenar o vetor em ordem decrescente (não-crescente)
void ordenarVetor(int vetor[TAM]) {
    int temp;
    // Algoritmo de ordenação (bubble sort adaptado)
    for (int i = 0; i < TAM - 1; i++) {
        for (int j = 0; j < TAM - i - 1; j++) {
            if (vetor[j] < vetor[j + 1]) { // troca se o próximo for maior
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// Função para imprimir o vetor
void imprimirVetor(int vetor[TAM], const char* mensagem) {
    printf("%s\n", mensagem);
    for (int i = 0; i < TAM; i++) {
        printf("%2d ", vetor[i]); // imprime cada elemento com 2 espaços
    }
    printf("\n");
}

int main() {
    int vetor[TAM];

    // Preencher vetor aleatoriamente
    preencherVetor(vetor);

    // Imprimir vetor original
    imprimirVetor(vetor, "Vetor Original:");

    // Ordenar vetor em ordem decrescente
    ordenarVetor(vetor);

    // Imprimir vetor ordenado
    imprimirVetor(vetor, "Vetor Ordenado (Decrescente):");

    return 0;
}
