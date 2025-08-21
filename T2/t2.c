//Hiago de Oliveira Mendes e Lucas Rocha Rangel

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_THREADS 4

// Estrutura com os dados que serão passados para cada Thread
typedef struct {
    int a, b;
    int tempo;
    char operacao[20];
} DadosThread;

// Função executada por cada Thread
void* executarOperacao(void* arg) {
    DadosThread* dados = (DadosThread*) arg;
    int resultado;

    // Determina qual operação realizar
    if (strcmp(dados->operacao, "SOM") == 0) {
        resultado = dados->a + dados->b;
    } else if (strcmp(dados->operacao, "SUB") == 0) {
        resultado = dados->a - dados->b;
    } else if (strcmp(dados->operacao, "MULT") == 0) {
        resultado = dados->a * dados->b;
    } else if (strcmp(dados->operacao, "DIV") == 0) {
        resultado = dados->a / dados->b;
    }

    // Imprime antes de dormir
    printf("Eu sou a Thread %s (%d) e vou dormir por %d segundos!\n",
           dados->operacao, resultado, dados->tempo);

    sleep(dados->tempo);

    // Imprime depois de dormir
    printf("Eu sou a Thread %s (%d). Ja se passaram %d segundos, entao terminei!\n",
           dados->operacao, resultado, dados->tempo);

    pthread_exit(NULL);
}

int main() {
    int a, b;
    pthread_t threads[MAX_THREADS];
    DadosThread dados[MAX_THREADS];
    char* operacoes[] = {"SOM", "SUB", "MULT", "DIV"};

    // Leitura dos valores de entrada
    printf("Digite o valor de a: ");
    scanf("%d", &a);

    do {
        printf("Digite o valor de b (b != 0): ");
        scanf("%d", &b);
    } while (b == 0);

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Cria e inicia as Threads
    for (int i = 0; i < MAX_THREADS; i++) {
        dados[i].a = a;
        dados[i].b = b;
        dados[i].tempo = (rand() % 20) + 1; // número entre 1 e 20
        strcpy(dados[i].operacao, operacoes[i]);

        pthread_create(&threads[i], NULL, executarOperacao, (void*)&dados[i]);
    }

    // Aguarda todas as Threads finalizarem
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
