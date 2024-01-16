/*Enunciado: Escribe un programa en C que le pida al usuario ingresar una 
cadena de caracteres y luego cuente y muestre en pantalla el número de vocales 
(mayúsculas y minúsculas) presentes en la cadena. El programa debe ser sensible 
a mayúsculas y minúsculas.

gcc contarVocales.c -o contarVocales
./contarVocales
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER 1024
int main() {

    char frase [BUFFER];
    int contadorVocales = 0;

    printf("Introduce una frase: ");
    fgets(frase, BUFFER, stdin);

    int longitud = strlen(frase);
    for (int i = 0; i <= longitud; i++) {
        char caracter = tolower(frase[i]);

        if (caracter == 'a' || caracter == 'e' || caracter == 'i' || caracter == 'o' || caracter == 'u'){
            contadorVocales++; 
        }
    }
    
    printf("Número de vocales en la cadena: %d\n", contadorVocales);

    return 0;
}