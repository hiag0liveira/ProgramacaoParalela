#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//para compilar usando gcc gcc q1.c -o q1.exe   
//executar .\q1.exe


void gerarMatriz(int m[4][5]);
bool verificarMatriz(const int m[4][5]);
void imprimirMatriz(const int m[4][5]);

int main(void) {
  int matriz[4][5];

  gerarMatriz(matriz);
  imprimirMatriz(matriz);

  if (verificarMatriz(matriz))
    puts("\nMatriz VALIDA ");
  else
    puts("\nMatriz INVALIDA ");

  return 0;
}

void gerarMatriz(int m[4][5]) {
  srand((unsigned)time(NULL));

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 5; ++j)
      m[i][j] = (rand() % 20) + 1;
}

bool verificarMatriz(const int m[4][5]) {
  int menorValor = 500;
  int maiorValor = 0;


    for (int j = 0; j < 5; ++j) {
        int soma = 0;
        for (int i = 0; i < 4; ++i)
            soma += m[i][j];
        if (soma < menorValor)
            menorValor = soma;
    }


    for (int i = 0; i < 4; ++i) {
        int prod = 1;
        for (int j = 0; j < 5; ++j)
            prod *= m[i][j];
        if (prod > maiorValor)
            maiorValor = prod;
    }
  printf("Menor valor: %2d \nMaior valor: %2d\n",menorValor,maiorValor);

  if(menorValor <= maiorValor){
    return true;
  } else {
    return false;
  }
  
  
}

void imprimirMatriz(const int m[4][5]) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j)
      printf("%2d ", m[i][j]);
    putchar('\n');
  }
}
