/*Crea un programa en c que reciba un número n y un número m.
El programa escribirá todos los números primos de la longitud n, utilizando m procesos.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <math.h>

int esPrimo(int numero) {
    if (numero <= 1) { // Los números menores o iguales a 1 no son primos
        return 0; 
    }

    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) { // El número no es primo
            return 0; 
        }
    }
    return 1; // El número es primo
}

/*trabajoDeHijo realiza el trabajo de cada hijo. Calcula un rango de números en función del 
número de procesos y del número introducido, y luego verifica si cada número en ese rango 
es primo utilizando la función esPrimo.*/
int trabajoDeHijo(int soy_hijo, int n_procesos, int nIntroducido) {
    // Definir el rango de números que cada proceso hijo verificará
    double rangoInicio = 1;
    double rangoFin = 10;

    // Calcular el rango basado en el número introducido
    if (nIntroducido == rangoInicio) {
        rangoInicio = nIntroducido;

    } else {
        double nPotenciaInicio = nIntroducido-1;
        double potenciaInicio = pow(rangoInicio, nPotenciaInicio);
        rangoInicio = potenciaInicio;
    }

    double potenciaFin = pow(rangoFin, nIntroducido);
    rangoFin = potenciaFin - 1;
    
    // Verificar si cada número en el rango es primo
    for (int i = rangoInicio; i <= rangoFin; i++) {
        if (i % n_procesos == soy_hijo) {
            if (esPrimo(i)) {
                printf("El numero %d es primo\n", i);
            } else {
                printf("El numero %d no es primo\n", i);
            }
        }
    }

    return 0;
}
int main() {

    int n_procesos;
    int nIntroducido;

    int soy_hijo = 0;

    // Solicitar entrada al usuario
    printf("Introduce un numero: \n");
    scanf("%d", &nIntroducido);

    printf("Introduce el numero de procesos: \n");
    scanf("%d", &n_procesos);

    pid_t id_hijos[n_procesos];

    // Crear procesos hijos
    for (soy_hijo = 0; soy_hijo < n_procesos; soy_hijo++) {
        id_hijos[soy_hijo] = fork();

        if (id_hijos[soy_hijo] == 0) {
            break; // Salir del bucle si es un proceso hijo
        }
    }

    if (soy_hijo == n_procesos) { // Soy el padre
        
        for (int i = 0; i < n_procesos; i++) {
            wait(NULL);
        }

    } else {
        // Soy un proceso hijo
        trabajoDeHijo(soy_hijo, n_procesos, nIntroducido);
    }

    return 0;
}