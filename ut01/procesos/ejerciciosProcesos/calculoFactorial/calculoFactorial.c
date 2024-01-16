/*Enunciado: Desarrolla un programa que permita al usuario 
ingresar un número entero no negativo y calcule su factorial. 
Asegúrate de manejar adecuadamente los casos de entrada inválida.

gcc calculoFactorial.c -o calculoFactorial
./calculoFactorial
*/

#include <stdio.h>
int main() {

    int num, resultado;
    
    do {
        printf("Introduce un numero: ");
        scanf("%d", &num);
    } while (num < 0);
    
    resultado = 1;

    for (int i = 0; i < num; i++) {
        resultado += resultado * i;
    }

    printf("El factorial del numero: %d es: %d\n", num, resultado);

    return 0;
}