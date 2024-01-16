/*Enunciado: Escribe un programa que permita al usuario 
ingresar una temperatura en grados Celsius y lo convierta 
a grados Fahrenheit utilizando la fórmula: Fahrenheit = (Celsius * 9/5) + 32.

gcc conversionGrados.c -o conversionGrados
./conversionGrados
*/
#include <stdio.h>

int main() {
    float celsius, fahrenheit;
    
    // Solicitar al usuario que ingrese la temperatura en grados Celsius
    printf("Introduce una temperatura en grados Celsius: ");
    scanf("%f", &celsius);

    // Calcular la temperatura en grados Fahrenheit utilizando la fórmula
    fahrenheit = (celsius * 9/5) + 32;

    // Mostrar el resultado al usuario
    printf("%.2f grados Celsius equivalen a: %.2f grados Fahrenheit.\n", celsius, fahrenheit);

    return 0;
}