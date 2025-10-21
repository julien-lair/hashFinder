#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

void get_hash_sha256(char* input, char* hash_output) {
    unsigned char output[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), output);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        sprintf(&hash_output[i*2], "%02x", output[i]);
    }
    hash_output[SHA256_DIGEST_LENGTH * 2] = '\0';
}