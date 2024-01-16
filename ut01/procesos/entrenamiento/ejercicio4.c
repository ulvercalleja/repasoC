/*Crea un programa que reciba un número n por parámetro. 
El programa creará n hijos y les enviará una señal a cada uno de ellos para matarlos.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    int nProcesos;
    pid_t pid_hijo;

    printf("Ingrese el numero de procesos: ");
    scanf("%d", &nProcesos);

    //Almacenar PIDs de hijos
    pid_t hijos[nProcesos];

    for (int i = 0; i < nProcesos; i++) { //Creación de procesos hijos:
        pid_t hijo = fork();

        if (hijo < 0) {
            
            perror("Error al crear el primer proceso hijo");
            return 1;

        } else if (hijo == 0) {
            hijo = getpid();
            printf("PID HIJO: %d\n", hijo);
            fflush(stdout); // Forzar la limpieza del búfer

            while (1) {
                sleep(1);
            }

        } else {
            //Codigo padre
            hijos[i] = hijo;
        }
    }

    // Espera antes de enviar las señales para que todos los hijos hayan sido creados
    sleep(2); 

    for (int i = 0; i < nProcesos; i++) { //Envia señal de matar hijos
        printf("Hijo muerto: %d\n", hijos[i]);
        kill(hijos[i], SIGKILL);
    }

    for (int i = 0; i < nProcesos; i++) { //Espera a que todos los hijos terminen
        wait(NULL);
    }

    return 0;
}