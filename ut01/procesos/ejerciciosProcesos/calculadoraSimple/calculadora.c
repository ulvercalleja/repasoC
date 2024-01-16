/*Enunciado: Crea un programa que solicite al usuario ingresar 
dos números enteros y muestre la suma de esos números en pantalla.

gcc calculadora.c -o calculadora
./calculadora
*/
#include <stdio.h>
int main() {
    int num1, num2;
    int suma;
    printf("Introduce un numero: ");
    scanf("%d", &num1);
    printf("Introduce el siguiente numero: ");
    scanf("%d", &num2);

    suma = num1 + num2;
    printf("La suma es %d\n", suma);
    return 0;
}