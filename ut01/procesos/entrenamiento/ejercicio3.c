/* Crea un programa que reciba por parámetro un número entero positivo n. 
Este número indicará el número de hijos. Cada hijo generará un fichero 
con la posibles combinación de caracteres de esa longitud. El hijo 1 una letra, 
el hijo 2 dos letras 'aa' a la 'zz', etc. Los nombres serán datos1.txt, datos2.txt, etc.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define MIN_HIJOS 0
#define NUM_HIJO 0
#define NUM_ERROR_HIJO -1
int main(int argc, char *argv[]) {
    
    int numHijos = atoi(argv[1]); // Leer numero introducido por parametros

     if (numHijos <= MIN_HIJOS) {
        printf("El número de hijos debe ser un entero positivo.\n");
        return 1;
    }

    for (int i = 0; i < numHijos; i++) { // Crear hijos
        pid_t hijo = fork();

        if (hijo == NUM_ERROR_HIJO) { // Comprobar si se ha creado hijo correctamente
            perror("Error al crear el primer hijo");
            exit(EXIT_FAILURE);
        } else if (hijo == NUM_HIJO) { // Proceso hijo
            char filename[15];

            // Dar nombre al archivo, datos+i
            sprintf(filename, "datos%d.txt", i); 

            // Abrir el archivo de salida
            FILE *file = fopen(filename, "w");

            char recorrerLetras[2];

            for (recorrerLetras[0] = 'a'; recorrerLetras[0] <= 'z'; recorrerLetras[0]++) {
                for (recorrerLetras[1] = 'a'; recorrerLetras[1] <= 'z'; recorrerLetras[1]++) {

                    printf("%s\n", recorrerLetras);
                    
                }
            }
        }


    }
    
    return 0;
}