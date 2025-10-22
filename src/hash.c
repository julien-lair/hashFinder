#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
void get_hash_sha512(char* input, char* hash_output) {
    unsigned char output[SHA512_DIGEST_LENGTH];
    SHA512((unsigned char*)input, strlen(input), output);

    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++){
        sprintf(&hash_output[i*2], "%02x", output[i]);
    }
    hash_output[SHA512_DIGEST_LENGTH * 2] = '\0';
}

void get_hash_sha384(char* input, char* hash_output) {
    unsigned char output[SHA384_DIGEST_LENGTH];
    SHA384((unsigned char*)input, strlen(input), output);

    for(int i = 0; i < SHA384_DIGEST_LENGTH; i++){
        sprintf(&hash_output[i*2], "%02x", output[i]);
    }
    hash_output[SHA384_DIGEST_LENGTH * 2] = '\0';
}

void get_hash_sha256(char* input, char* hash_output) {
    unsigned char output[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), output);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        sprintf(&hash_output[i*2], "%02x", output[i]);
    }
    hash_output[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void get_hash_sha224(char* input, char* hash_output) {
    unsigned char output[SHA224_DIGEST_LENGTH];
    SHA224((unsigned char*)input, strlen(input), output);

    for(int i = 0; i < SHA224_DIGEST_LENGTH; i++){
        sprintf(&hash_output[i*2], "%02x", output[i]);
    }
    hash_output[SHA224_DIGEST_LENGTH * 2] = '\0';
}

void get_hash_md5(char* input, char* hash_output) {
    unsigned char output[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)input, strlen(input), output);

    for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
        sprintf(&hash_output[i*2], "%02x", output[i]);
    }
    hash_output[MD5_DIGEST_LENGTH * 2] = '\0';
}


