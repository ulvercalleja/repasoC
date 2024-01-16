/* Tenemos N procesos hijos creado con fork. El proceso padre enviará señales aleatorias
a sus hijos. El numero de señales a enviar lo recibe el padre por parámetro de línea de comandos.
El padre almacena en un array los ids de los hijos, el padre enviará cada señal a un hijo aleatorio.
A lo largo del juego el padre puede enviar más de una señal a un hijo. El hijo tiene un bucle principal
infinito en el que no hace nada más que sleep. El hijo al recibir la primera señal USER1 escribe "soy el hijo XXXXX.
He sido eliminado", si se envía de nuevo la señal escribe "soy el hijo XXXXX. He vuelto a ser eliminado". Los hijos
al recibir la señal SIGINT escriben por pantalla si han sido eliminados y finalizan.

Resumen, el padre enviará n señales USER1 y luego una señal SIGINT a cada hijo. El padre es un proceso educado y 
espera a que sus hijos terminen. Los hijos escriben si han sido eliminados o no.

gcc ejercicio2.c -o ejercicio2
./ejercicio2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <sys/wait.h> // Agrega esta línea para incluir la declaración de waitpid
#include <time.h>
#include <string.h>
#include <signal.h>

#define READ 0
#define WRITE 1
#define N_PROCESOS 5
#define TRUE 1
#define FALSE 0

void sigint_handler1(int signo) {
    printf("He sido eliminado\n");
}
void sigint_handler2(int signo) {
    printf("He sido eliminado otra vez\n");
    exit(0);
}

int main(int argc, char *argv[]) {
     srand(time(NULL));

    int n_señales = atoi(argv[1]);

    pid_t pid_hijo;

    pid_t hijos[N_PROCESOS];

    for (int i = 0; i < N_PROCESOS; i++) {
        pid_t hijo = fork();

        if (hijo < 0) {
            perror("Error al crear el primer proceso hijo");
            return 1;
        } else if (hijo == 0) {
            pid_hijo = getpid();

            printf("Soy el hijo: %d. ", pid_hijo);
            signal(SIGUSR1, sigint_handler1);
            signal(SIGINT, sigint_handler2);
            break;
            while (1) {
                sleep(1);
            }
        } else {
            hijos[i] = hijo;
        }
    }
    sleep(2);
    int seguir = TRUE;

    while (seguir) {
        int señalRandom;
        for (int i = 0; i < n_señales; i++) {
            señalRandom = rand() % N_PROCESOS;
            kill(hijos[señalRandom], SIGUSR1);
        }
        for (int i = 0; i < n_señales; i++) {
            señalRandom = rand() % N_PROCESOS;
            kill(hijos[señalRandom], SIGINT);
        }
        if (hijos[N_PROCESOS] == 0) {
            seguir = FALSE;
        }
    }

    for (int i = 0; i <= N_PROCESOS; i++) {
        wait(NULL);
    }

    return 0;
}