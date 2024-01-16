/*Enunciado: Los arrays pueden ser de cualquier tipo de dato. 
Crea un programa que pida al usuario las notas que ha sacado en 
5 exámenes. Almacena la información en un array. Después mostrará 
una lista con la nota de los exámenes y si ha aprobado o no. 
La nota media, la nota más alta y la nota más baja.

gcc arrayNumeros.c -o arrayNumeros
./arrayNumeros
*/
#include <stdio.h>
#include <stdlib.h>
#define NUM_NOTAS 5
#define APROBADO 5

int main() {
    int notas[NUM_NOTAS];
    int notaMax, notaMin;
    float notaMedia;

    for (int i = 1; i <= NUM_NOTAS; i++) {
        printf("Introduce tu nota del examen %d: ", i);
        scanf("%d", &notas[i]);
    }

    notaMax = 0;
    notaMin = 10;

    for (int i = 1; i <= NUM_NOTAS; i++) {

        if (notas[i] >= APROBADO) {
            printf("Nota examen %d: %d - APROBADO\n", i, notas[i]);
        } else {
            printf("Nota examen %d: %d - SUSPENSO\n", i, notas[i]);
        }

        if (notas[i] > notaMax) {
            notaMax = notas[i];
        } else if (notas[i] < notaMin){
            notaMin = notas[i];
        }

        notaMedia += notas[i];
    }
    
    printf("La nota minima ha sido: %d\n", notaMin);
    printf("La nota maxima ha sido: %d\n", notaMax);
    printf("La nota media ha sido: %.2f\n", notaMedia/NUM_NOTAS);

    return 0;
}