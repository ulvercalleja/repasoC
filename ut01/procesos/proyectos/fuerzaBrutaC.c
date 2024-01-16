#include <stdio.h>
#include <string.h>
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
    
    /*aaaa-zzzz
    for (current[0] = 'a'; current[0] <= 'z'; current[0]++) {
        for (current[1] = 'a'; current[1] <= 'z'; current[1]++) {
            for (current[2] = 'a'; current[2] <= 'z'; current[2]++) {
                for (current[3] = 'a'; current[3] <= 'z'; current[3]++) {

                    printf("%s\n", current);
                }
            }
        }
    }
*/
    char hash1[] = "582fc884d6299814fbd4f12c1f9ae70f";
    char hash2[] = "74437fabd7c8e8fd178ae89acbe446f2";
    char hash3[] = "28ea19352381b8659df830dd6d5c90a3";
    char hash4[] = "90f077d7759d0d4d21e6867727d4b2bd";
    char hash_str[50];
    char current[5];  
    unsigned char result[MD5_LEN];

    for (current[0] = 'a'; current[0] <= 'z'; current[0]++) {
        for (current[1] = 'a'; current[1] <= 'z'; current[1]++) {
            for (current[2] = 'a'; current[2] <= 'z'; current[2]++) {
                for (current[3] = 'a'; current[3] <= 'z'; current[3]++) {
                    generateMD5(current, hash_str);
                    
                    if (strcmp(hash_str, hash1) == 0) {
                        printf("Found a matching string: %s\n", current);
                        
                    }

                    if (strcmp(hash_str, hash2) == 0) {
                        printf("Found a matching string: %s\n", current);
                        
                    }

                    if (strcmp(hash_str, hash3) == 0) {
                        printf("Found a matching string: %s\n", current);
                        
                    }

                    if (strcmp(hash_str, hash4) == 0) {
                        printf("Found a matching string: %s\n", current);
                        return 0;
                    }

                }
            }
        }
    }

    return 0;
}