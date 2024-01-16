/*Crea un proceso que cree dos procesos hijos, luego 
generará N (20) números aleatorios. Enviará los pares 
al primer hijo, los impares al segundo. Los hijos escribirán 
por pantalla "Soy el hijo 1|2, he recibido ". Por cada número 
que mande el padre.

gcc ejercicio2.c -o ejercicio2
./ejercicio2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1
#define NTOTALES 20
int main(int argc, char *argv[]) {
    int numerosAleatorios;
    int pipePares[2], pipeImpares[2];

    if (pipe(pipePares) == -1) {
        perror("No se ha creado el pipe o tubería");
        return 1;
    }

    if (pipe(pipeImpares) == -1) {
        perror("No se ha creado el pipe o tubería");
        return 1;
    }

    pid_t hijo1 = fork();

    if (hijo1 == -1) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (hijo1 == 0){ // Código del proceso hijo1
        close(pipePares[WRITE]); // El padre no leerá del pipe, así que cerramos el descriptor de lectura
        
        while (read(pipePares[READ], &numerosAleatorios, sizeof(numerosAleatorios)) > 0) {
            printf("Soy el hijo 1 he recibido el numero: %d\n", numerosAleatorios);
        }
    }

    pid_t hijo2 = fork();

    if (hijo2 == -1) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (hijo2 == 0){ // Código del proceso hijo2
        close(pipeImpares[WRITE]); // El padre no leerá del pipe, así que cerramos el descriptor de lectura

        while (read(pipeImpares[READ], &numerosAleatorios, sizeof(numerosAleatorios)) > 0) {
            printf("Soy el hijo 2 he recibido el numero: %d\n", numerosAleatorios);
        }
        
    } else {
        // Semilla para la generación de números aleatorios
        srand(time(NULL));
        for (int i = 0; i <= NTOTALES; i++) {
            numerosAleatorios = rand() % 101;
            if ((numerosAleatorios % 2) == 0) {
                close(pipePares[READ]); // El padre no leerá del pipe, así que cerramos el descriptor de lectura
                write(pipePares[WRITE], &numerosAleatorios, sizeof(numerosAleatorios)); // Escribimos los números en el pipe
            } else {
                close(pipeImpares[READ]); // El padre no leerá del pipe, así que cerramos el descriptor de lectura
                write(pipeImpares[WRITE], &numerosAleatorios, sizeof(numerosAleatorios)); // Escribimos los números en el pipe
            }
            
        }
    }

    return 0;
}