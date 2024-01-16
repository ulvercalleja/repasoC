/* Crea un programa de adivina el número con las siguientes características:

El programa padre creará un proceso hijo. El cual será el que controle el número aleatorio.
El proceso hijo generará un número aleatorio.
El proceso hijo recibirá por un pipe números.
El proceso hijo emitirá una SIGUSR1, SIGUSR2, SIGINT al proceso padre getppid. Cuando el número 
sea mayor emitirá SIGUSR1, si es menor SIGUSR2 y si es el número SIGINT.
El proceso hijo termina cuando recibe SIGINT.
El programa padre pedirá números al usuario y los enviará por el pipe al hijo.
Cuando el programa padre reciba la señal SIGINT será que el usuario ha acertado, mostrará un mensaje. 
Después el padre emitirá otra SIGINT al hijo para que finalice.

gcc adivinaNumeroJavi.c -o adivinaNumeroJavi
./adivinaNumeroJavi
*/

#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define MAXRANDGENNUM 100
#define MAXROUND 5
#define READ 0
#define WRITE 1

/*el funcionamiento de este ejercicio es un adivinar el numero entre el padre
y el hijo usando señales te dira si es mayor, menor o lo has acertado*/

void manejadorSenialesSIGUSR1(int signal) {
}
void manejadorSenialesSIGUSR2(int signal){
}
void manejadorSenialesSIGINT(int signal){
    exit(0);
}

int main(int argc, char const *argv[]) {
    
    int pipeHijo[2];

    if (pipe(pipeHijo) != 0) {
        printf("el pipe ha fallado\n");
        return 1;
    }

    pid_t hijo;

    if ((hijo = fork()) == 0) {
        close(pipeHijo[READ]);

        srand(time(NULL));
        int numeroAleatorio = rand() % MAXRANDGENNUM;

        write(pipeHijo[WRITE], &numeroAleatorio, sizeof(int));

        signal(SIGUSR1, manejadorSenialesSIGUSR1);
        signal(SIGUSR1, manejadorSenialesSIGUSR2);

        for (int i = 0; i < MAXROUND; i++) {
            pause();
        }
        exit(0);
    } else {
        close(pipeHijo[WRITE]);

        int numeroRandomRecibido;
        read(pipeHijo[READ], &numeroRandomRecibido, sizeof(int));

        int numero=0;
        printf("ponme un numero y a ver si lo aciertas, tienes %d intentos\n", MAXROUND);
        scanf("%d", &numero);

        for (int i = 1; i < MAXROUND; i++) {
            if (numero > numeroRandomRecibido) {
                printf("Te has pasado, mas bajo el numero\n");
                kill(hijo, SIGUSR1);

                printf("Elige otro: ");
                scanf("%d", &numero);
            } else if (numero < numeroRandomRecibido) {
                printf("Te has quedado corto, mas alto el numero\n");
                kill(hijo, SIGUSR1);

                printf("Elige otro: ");
                scanf("%d", &numero);
            } else {
                kill(hijo, SIGUSR2);
                printf("La has clavado");
                break;
            } if(i==MAXROUND-1){
                printf("Al final no lo has acertado, el numero era %d\n",numeroRandomRecibido);
            }
        }
    }
    waitpid(hijo, NULL, 0);

    return 0;
}