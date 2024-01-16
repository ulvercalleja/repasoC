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
   
    char hash1[] = "f4a1c8901a3d406f17af67144a3ec71a";
    char hash2[] = "d66e29062829e8ae0313adc5a673f863";

    char hash_str[80];
    char current[6];  
    unsigned char result[MD5_LEN];

    for (current[0] = 'A'; current[0] <= 'z'; current[0]++) {
        for (current[1] = 'A'; current[1] <= 'z'; current[1]++) {
            for (current[2] = 'A'; current[2] <= 'z'; current[2]++) {
                for (current[3] = 'A'; current[3] <= 'z'; current[3]++) {
                    for (current[4] = 'A'; current[4] <= 'z'; current[4]++) {
                    generateMD5(current, hash_str);
                    
                        if (strcmp(hash_str, hash1) == 0) {
                            printf("Found a matching string: %s\n", current);
                            
                        }

                        if (strcmp(hash_str, hash2) == 0) {
                            printf("Found a matching string: %s\n", current);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    return 0;
}