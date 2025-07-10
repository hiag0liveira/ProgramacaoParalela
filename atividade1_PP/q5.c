
#include <stdio.h>

// Função recursiva para calcular a^b
int potencia(int a, int b) {
    if (b == 0) {
        return 1; // caso base: qualquer número elevado a 0 é 1
    } else {
        return a * potencia(a, b - 1); // chamada recursiva
    }
}

int main() {
    int a, b;

    // Ler os números do teclado
    printf("Digite o valor de a (a != 0): ");
    scanf("%d", &a);

    printf("Digite o valor de b (b >= 0): ");
    scanf("%d", &b);

    // Verificar restrições
    if (a == 0 || b < 0) {
        printf("Valores invalidos! a deve ser diferente de 0 e b >= 0.\n");
        return 1;
    }

    // Calcular e imprimir a^b
    int resultado = potencia(a, b);
    printf("%d elevado a %d = %d\n", a, b, resultado);

    return 0;
}
