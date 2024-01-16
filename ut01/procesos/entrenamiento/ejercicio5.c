/*Crea un proceso que sea capaz de gestionar un señal definida por el usuario. Luego hará fork y el padre le enviará la señas al hijo. 
Al gestionar la señal el hijo escribirá "Recibido y terminará el proceso."*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>


void sigint_handler(int signo) { // Manejador de señales

    pid_t hijo = fork(); 
    pid_t pid_hijo; // Variable que se utilizará para almacenar el PID del hijo 

    if (hijo < 0) {
        perror("Error al crear el primer proceso hijo");
    } else if (hijo == 0) { //Codigo del hijo
        pid_hijo = getpid();

        //Imprime el PID del proceso hijo y el número de señal recibida.
        printf("PID hijo muerto: %d, Señal recibida: %d\n", pid_hijo, signo);
        exit(0);
    }
}

int main() {
    signal(SIGUSR1, sigint_handler);
    
    while (1) {
        sleep(1);
    }

    return 0;
}

/*PARA COMPROBAR QUE EL PROGRAMA FUNCIONA:
Una vez compilado y ejecutado, abre otra terminal y obtén el PID del programa ejercicio5. Puedes usar el comando ps o pgrep:
ps aux | grep ejercicio5 O pgrep ejercicio5
Luego, envía una señal SIGUSR1 al proceso usando el comando kill:
kill -SIGUSR1 PID_del_ejercicio5
Reemplaza PID_del_ejercicio5 con el PID real que hayas obtenido.

Verificación:
Deberías ver un mensaje impreso en la primera terminal donde está en ejecución el programa ejercicio5. El mensaje indicará el PID del proceso hijo 
y el número de la señal recibida.
PID hijo muerto: XXXX, Señal recibida: 10
El número XXXX será el PID del proceso hijo.*/