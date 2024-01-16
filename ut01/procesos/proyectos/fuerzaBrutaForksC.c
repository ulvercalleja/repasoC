#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <openssl/evp.h>

#define MD5_LEN 16

void generateMD5(const char *string, unsigned char *str_result) {
    EVP_MD_CTX *ctx;
    const EVP_MD *md;
    unsigned char result[EVP_MAX_MD_SIZE];

    ctx = EVP_MD_CTX_new();
    md = EVP_md5();

    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, string, strlen(string));
    EVP_DigestFinal_ex(ctx, result, NULL);

    EVP_MD_CTX_free(ctx);

    for(int i = 0; i < MD5_LEN; i++){   // MD5 result is always 16 bytes
        sprintf(str_result+(i*2),"%02x", result[i]);
    }
}

int main() {
   
    char hash1[] = "f4a1c8901a3d406f17af67144a3ec71a";
    char hash2[] = "d66e29062829e8ae0313adc5a673f863";
    char current[6];
    unsigned char result[MD5_LEN];

    // Crear dos procesos hijos
    pid_t child1, child2;

    child1 = fork();

    if (child1 < 0) {
        perror("Error al crear el primer proceso hijo");
        return 1;
    }

    if (child1 == 0) {
        // Este es el primer proceso hijo
        // Realiza la mitad de la fuerza bruta

        for (current[0] = 'A'; current[0] <= 'm'; current[0]++) {
            for (current[1] = 'A'; current[1] <= 'z'; current[1]++) {
                for (current[2] = 'A'; current[2] <= 'z'; current[2]++) {
                    for (current[3] = 'A'; current[3] <= 'z'; current[3]++) {
                        for (current[4] = 'A'; current[4] <= 'z'; current[4]++) {
                            generateMD5(current, result);
                            if (strcmp(result, hash1) == 0) {
                                printf("Proceso 1: Encontrada una coincidencia: %s\n", current);
                            }
                        }
                    }
                }
            }
        }
    } else {
        // Este es el proceso padre

        child2 = fork();

        if (child2 < 0) {
            perror("Error al crear el segundo proceso hijo");
            return 1;
        }

        if (child2 == 0) {
            // Este es el segundo proceso hijo
            // Realiza la otra mitad de la fuerza bruta

            for (current[0] = 'n'; current[0] <= 'z'; current[0]++) {
                for (current[1] = 'A'; current[1] <= 'z'; current[1]++) {
                    for (current[2] = 'A'; current[2] <= 'z'; current[2]++) {
                        for (current[3] = 'A'; current[3] <= 'z'; current[3]++) {
                            for (current[4] = 'A'; current[4] <= 'z'; current[4]++) {
                                generateMD5(current, result);
                                if (strcmp(result, hash1) == 0) {
                                    printf("Proceso 2: Encontrada una coincidencia: %s\n", current);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            // Este es el proceso padre
            // Espera a que ambos hijos terminen
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}