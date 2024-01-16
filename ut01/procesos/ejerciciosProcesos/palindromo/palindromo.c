/*Enunciado: Crea un programa en C que determine si una palabra 
o frase ingresada por el usuario es un palíndromo o no. Un palíndromo
es una palabra o frase que se lee igual de izquierda a derecha y de derecha
a izquierda, ignorando espacios y signos de acentuación. El programa debe 
eliminar los espacios y considerar solo las letras en la verificación.

gcc palindromo.c -o palindromo
./palindromo
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER 1024

void quitarEspacios(char *cadena){ //Esta funciona recibe la frase

    int i, j = 0;
    for (i = 0; cadena[i]; i++) {
        if (cadena[i] != ' ') {
            cadena[j++] = cadena[i];
        }
    }
    cadena[j] = '\0';
}

int esPalindromo(const char *cadena) {
    int longitud = strlen(cadena);
    for (int i = 0; i < longitud / 2; i++) {
        if (tolower(cadena[i]) != tolower(cadena[longitud - i - 1])) {
            return 0; // No es un palíndromo
        }
    }
    return 1; // Es un palíndromo
}

int main() {

    char cadena [BUFFER];

    printf("Introduce una frase: ");
    fgets(cadena, BUFFER, stdin);
    
    quitarEspacios(cadena);
    
    if (esPalindromo(cadena)) {
        printf("La palabra o frase ingresada es un palíndromo.\n");
    } else {
        printf("La palabra o frase ingresada no es un palíndromo.\n");
    }

    return 0;
}


