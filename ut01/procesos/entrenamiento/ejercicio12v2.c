#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Función que verifica si un número es primo o no
int esPrimo(int num) {
    if (num < 2) {
        return 0; // No es primo
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // No es primo
        }
    }

    return 1; // Es primo
}

// Función que encuentra números primos en un rango dado
void encontrarPrimos(int inicio, int fin) {
    for (int i = inicio; i <= fin; i++) {
        if (esPrimo(i)) {
            printf("%d\n", i);
        }
    }
}

int main(int argc, char *argv[]) {
    // Verifica que se proporcionen la cantidad correcta de argumentos
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <longitud_n> <num_procesos>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Convierte los argumentos a enteros
    int longitud_n = atoi(argv[1]);
    int num_procesos = atoi(argv[2]);

    // Verifica que los argumentos sean enteros positivos
    if (longitud_n <= 0 || num_procesos <= 0) {
        fprintf(stderr, "Los argumentos deben ser enteros positivos.\n");
        return EXIT_FAILURE;
    }

    int inicio = 1;
    int fin = 1;
    int rango = longitud_n / num_procesos;

    for (int i = 0; i < num_procesos; i++) {
        // Calcula el rango para cada proceso hijo
        if (i == num_procesos - 1) {
            fin = longitud_n;
        } else {
            fin = inicio + rango - 1;
        }

        // Crea un nuevo proceso hijo
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error al crear el proceso hijo");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            // Código ejecutado por el proceso hijo
            printf("Proceso hijo %d:\n", i + 1);
            encontrarPrimos(inicio, fin);
            exit(EXIT_SUCCESS); // Sale del proceso hijo
        } else {
            // Código ejecutado por el proceso padre
            wait(NULL); // Espera a que el proceso hijo termine
            inicio = fin + 1;
        }
    }

    return EXIT_SUCCESS;
}