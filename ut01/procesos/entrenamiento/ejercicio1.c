/*Crea un proceso que cree un proceso hijo, el envíe 
3 números enteros aleatorios a través de un pipe. El 
proceso hijo los ordenará y los escribirá en el fichero salida.txt.

gcc ejercicio1.c -o ejercicio1
./ejercicio1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1
int main() {

    int numerosAleatorios[3];
    int tuberia[2];

    if (pipe(tuberia) == -1) {
        perror("No se ha creado el pipe o tubería");
        return 1;
    }

    pid_t hijo = fork();

    if (hijo == -1) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (hijo > 0){ // Código del proceso padre al ser mayor de 0

        close(tuberia[READ]);  // Cerramos el extremo de lectura del pipe en el padre

        // Semilla para la generación de números aleatorios
        srand(time(NULL));
        for (int i = 0; i < 3; i++) {
            numerosAleatorios[i] = rand() % 101;
        }

        // Imprimir los números generados por el padre
        printf("Padre: Números generados: %d, %d, %d\n", numerosAleatorios[READ], numerosAleatorios[1], numerosAleatorios[2]);

        write(tuberia[WRITE], numerosAleatorios, sizeof(numerosAleatorios));
        close(tuberia[WRITE]);  // Cerramos el extremo de escritura del pipe en el padre

        wait(NULL); // Esperar a que el hijo termine
    } else {
         close(tuberia[WRITE]);  // Cerramos el extremo de escritura del pipe en el hijo

         read(tuberia[READ], numerosAleatorios, sizeof(numerosAleatorios));
        // Ordenar los números
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2 - i; j++) {
                if (numerosAleatorios[j] > numerosAleatorios[j + 1]) {
                    int temp = numerosAleatorios[j];
                    numerosAleatorios[j] = numerosAleatorios[j + 1];
                    numerosAleatorios[j + 1] = temp;
                }
            }
        }
        // Imprimir los números ordenados por el hijo
        printf("Hijo: Números ordenados: %d, %d, %d\n", numerosAleatorios[0], numerosAleatorios[1], numerosAleatorios[2]);
        // Escribir los números en el pipe
        close(tuberia[READ]);  // Cerramos el extremo de lectura del pipe en el hijo

        // Escribir numeros en archivo salida.txt
        FILE *archivo_salida = fopen("salida.txt", "w");
        fprintf(archivo_salida, "%d %d %d\n", numerosAleatorios[0], numerosAleatorios[1], numerosAleatorios[2]);
        fclose(archivo_salida);
    }

    return 0;
}