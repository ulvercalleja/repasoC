#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
/* El programa crea varios procesos hijos, cada uno de los cuales realiza operaciones 
matemáticas (multiplicaciones) y muestra los resultados en la salida estándar. El proceso padre espera 
a que todos los hijos terminen antes de finalizar. Cada hijo tiene su propio número identificador y PID, 
lo que se refleja en los mensajes impresos.*/

#define NUMHIJOS 10 // Número de hijos que se van a crear
#define MULTIPLICAR 9 // Valor máximo por el que se va a multiplicar

int main() {
    srand(time(NULL)); // Inicializar la semilla para números aleatorios

    for (int i = 0; i < NUMHIJOS; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Código del hijo
            printf("SOY HIJO %d (PID: %d) REALIZANDO MULTIPLICACIONES\n", i, getpid());
            for (int j = 0; j < MULTIPLICAR; j++) {
                int num = i * j;
                printf("%d por %d es igual a %d\n", i, j, num);
            }
            exit(0);
        }
    }

    // El padre espera a que todos los hijos terminen
    for (int i = 0; i < NUMHIJOS; i++) {
        wait(NULL);
    }

    return 0;
}