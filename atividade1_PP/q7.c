
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 50 // tamanho do vetor

// preenchendo o vetor com numeros aleatórios de 1 a 100
void preencherVetor(int vetor[TAM]) {
    srand(time(NULL)); // inicializa gerador aleatório
    for (int i = 0; i < TAM; i++) {
        vetor[i] = (rand() % 100) + 1; // números entre 1 e 100
    }
}

// Função para imprimir o vetor
void imprimirVetor(int vetor[TAM]) {
    printf("Vetor:\n");
    for (int i = 0; i < TAM; i++) {
        printf("%3d ", vetor[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
}

// Função recursiva para encontrar o maior elemento do vetor
int encontrarMaior(int vetor[TAM], int indice, int maiorAtual) {
    // Se tiver percorrido todos os elementos, retorna o maior
    if (indice == TAM) {
        return maiorAtual;
    }

    // Atualizar o maior valor caso for necessário
    if (vetor[indice] > maiorAtual) {
        maiorAtual = vetor[indice];
    }

    // Chamadada recursiva para o prox elemento
    return encontrarMaior(vetor, indice + 1, maiorAtual);
}

int main() {
    int vetor[TAM];

    // Preencher vetor aleatoriamente
    preencherVetor(vetor);

    // Imprimir vetor
    imprimirVetor(vetor);

    // Encontrar o maior valor usando recursão
    int maior = encontrarMaior(vetor, 0, vetor[0]);

    printf("\nMaior valor do vetor: %d\n", maior);

    return 0;
}
