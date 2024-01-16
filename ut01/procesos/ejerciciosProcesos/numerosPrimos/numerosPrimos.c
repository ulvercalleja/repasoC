/*Enunciado: Crea un programa que solicite al usuario ingresar 
un número entero positivo y determine si es un número primo o no.

gcc numerosPrimos.c -o numerosPrimos
./numerosPrimos
*/

#include <stdio.h>
int main() {
    int num, cont;
    printf("Introduce un numero: ");
    scanf("%d", &num);

    for (int i = 1; i <= num; i++) {
        if (num % i == 0){
            cont ++;
        }
    }
    
    if (cont == 2){
        printf("El numero: %d es primo.\n", num);
    } else {
        printf("El numero: %d NO es primo.\n", num);
    }
    
    return 0;
}