/*Solo habrá dos hijos, el hijo que reciba un número primo pierde. Si ninguno recibe un número primo se salvan.
El padre recibirá por parámetro 2 números: el primero será la longitud de los números (si es 2 los números serán
entre 10 y 99, si 3 100-999, etc) el segundo será la cantidad de números a enviar. Cada hijo recibirá por un pipe
los números primos, indicará por pantalla el número recibido y si es primo o no. El padre espera a que sus hijos finalicen,
después indica qué hijos han sobrevivido. Deberá esperar por PID en concreto para saber si se ha salvado el hijo 1 o el 2.

gcc ejercicio1.c -o ejercicio1
./ejercicio1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>

#define READ 0
#define WRITE 1
#define PRIMO 1
#define NO_PRIMO 2
#define N_PROCESOS 2
// Función para verificar si un número es primo
bool esPrimo(int numero) {
    if (numero <= 1) {
        return false;
    }
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Error: Uso incorrecto. Se requieren 2 argumentos.\n");
        printf("Uso: %s <numero1> <numero2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    int numerosAleatorios;
    int pipe1[2], pipe2[2];

    if (pipe(pipe1) == -1) {
        perror("No se ha creado el pipe o tubería");
        return 1;
    }

    if (pipe(pipe2) == -1) {
        perror("No se ha creado el pipe o tubería");
        return 0;
    }

    pid_t hijo1 = fork();

    if (hijo1 == -1) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (hijo1 == 0){ // Código del proceso hijo1
        close(pipe1[WRITE]); 
        close(pipe2[WRITE]);
        close(pipe2[READ]);

        while (read(pipe1[READ], &numerosAleatorios, sizeof(numerosAleatorios)) > 0) {
            printf("Soy el hijo 1 he recibido el numero: %d\n", numerosAleatorios);

            if (esPrimo(numerosAleatorios)) {
                printf("Soy el hijo 1 ¡¡HE RECIBIDO UN NUMERO PRIMO!!\n");
                exit(PRIMO);
                close(pipe1[READ]);
            }
            
        }
    }

    pid_t hijo2 = fork();

    if (hijo2 == -1) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (hijo2 == 0){ // Código del proceso hijo2
        close(pipe1[WRITE]); 
        close(pipe2[WRITE]); 
        close(pipe1[READ]);

        while (read(pipe2[READ], &numerosAleatorios, sizeof(numerosAleatorios)) > 0) {
            printf("Soy el hijo 2 he recibido el numero: %d\n", numerosAleatorios);

            if (esPrimo(numerosAleatorios)) {
                printf("Soy el hijo 2 ¡¡HE RECIBIDO UN NUMERO PRIMO!!\n");
                exit(PRIMO);
                close(pipe2[READ]);
            }
            
        }
        
    } else {
        
        close(pipe1[READ]);  // Cerramos el extremo de lectura del pipe en el padre
        close(pipe2[READ]);

        srand((unsigned)time(NULL));

        for (int i = 0; i < num2; i++) {
        int numero = rand() % (num1 * 10) + (num1 == 2 ? 10 : 100);

        if (i % 2 == 0) {
            write(pipe1[1], &numero, sizeof(numero)); // Enviamos al primer hijo
        } else {
            write(pipe2[1], &numero, sizeof(numero)); // Enviamos al segundo hijo
        }
    }

    close(pipe1[WRITE]); // Cerramos el extremo de escritura del pipe del primer hijo
    close(pipe2[WRITE]); // Cerramos el extremo de escritura del pipe del segundo hijo

    // Esperar a que los procesos hijos terminen
        for (int i = 0; i < N_PROCESOS; i++){
            sleep(1);
            // Código del padre
            int status;
            int hijo = wait(&status);

            if (WIFEXITED(status) && WEXITSTATUS(status) == PRIMO) {
                    printf("El hijo %d ha muerto\n", hijo);
            } else {
                    printf("El hijo %d ha sobrevivido\n", hijo);
            }
        }
    }

    return 0;
}