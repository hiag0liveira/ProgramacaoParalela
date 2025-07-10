
#include <stdio.h>

#define TAM 20 // tamanho do vetor

// Função para preencher o vetor com números naturais > 1
void preencherVetor(int vetor[TAM]) {
    printf("Digite %d numeros naturais maiores que 1:\n", TAM);
    for (int i = 0; i < TAM; i++) {
        do {
            printf("Elemento %d: ", i + 1);
            scanf("%d", &vetor[i]);
            if (vetor[i] <= 1) {
                printf("O numero deve ser maior que 1. Tente novamente.\n");
            }
        } while (vetor[i] <= 1); // garante números maiores que 1
    }
}

// Função recursiva auxiliar para contar divisores
int contarDivisores(int n, int divisor) {
    if (divisor > n) {
        return 0; // caso base: passou de n
    }
    if (n % divisor == 0) {
        return 1 + contarDivisores(n, divisor + 1);
    } else {
        return contarDivisores(n, divisor + 1);
    }
}

// Função recursiva para verificar se um número é composto
int ehComposto(int n) {
    int totalDivisores = contarDivisores(n, 1);
    if (totalDivisores > 2) {
        return 1; // composto
    } else {
        return 0; // não composto
    }
}

// Função recursiva para organizar o vetor
void organizarVetor(int vetor[TAM], int inicio, int fim) {
    // caso base: quando os índices se cruzam
    if (inicio >= fim) {
        return;
    }

    if (ehComposto(vetor[inicio])) {
        // se já é composto, avança para o próximo
        organizarVetor(vetor, inicio + 1, fim);
    } else {
        // se não é composto, troca com o elemento do fim
        int temp = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = temp;
        // chama recursivamente com fim reduzido
        organizarVetor(vetor, inicio, fim - 1);
    }
}

// Função para imprimir o vetor
void imprimirVetor(int vetor[TAM], const char* mensagem) {
    printf("%s\n", mensagem);
    for (int i = 0; i < TAM; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int vetor[TAM];

    // Preenche o vetor com números lidos do teclado
    preencherVetor(vetor);

    // Imprime vetor original
    imprimirVetor(vetor, "\nVetor Original:");

    // Organiza o vetor de forma recursiva
    organizarVetor(vetor, 0, TAM - 1);

    // Imprime vetor organizado
    imprimirVetor(vetor, "\nVetor Organizado (Compostos primeiro):");

    return 0;
}
