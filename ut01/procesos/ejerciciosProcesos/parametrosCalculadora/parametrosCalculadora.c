/*Enunciado: Crea un programa que permita hacer lo siguiente: 
primer parámetro operación suma, resta, multiplicación o división. Si es 
división el segundo operador no puede ser 0. Ten en cuenta que necesita al 
menos 3 parámetros, de lo contrario deberá aparecer un mensaje de error.

gcc parametrosCalculadora.c -o parametrosCalculadora
./parametrosCalculadora
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Error: Uso incorrecto. Se requieren 3 argumentos.\n");
        printf("Uso: %s <cadena> <numero1> <numero2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    float resultado;

    char *operacion = argv[1];
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);

    if (strcmp(operacion, "suma") == 0) {
        resultado = num1 + num2;
    } else if (strcmp(operacion, "resta") == 0) {
        resultado = num1 - num2;
    } else if (strcmp(operacion, "multiplicacion") == 0) {
        resultado = num1 * num2;
    } else if (strcmp(operacion, "dividir") == 0) {
        if (num2 == 0) {
            printf("El operador no puede ser 0.");
            return EXIT_FAILURE;
        } else {
            resultado = (float)num1 / num2;
        }
    } else {
        printf("Operación no válida. Use suma, resta, multiplicacion o dividir.\n");
        return EXIT_FAILURE;
    }
    
    printf("El resultado de la operacion es %.2f\n", resultado);
    return 0;
}