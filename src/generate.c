#include <stdio.h>
#include <stdlib.h>
#include "hash.c"

void generate_t3c(char* input_file_path, char* output_file_path, char* algorithm){
    // Génération de la table T3C
    //fichier d'entrée
    FILE *inputFile;
    inputFile = fopen(input_file_path,"r");
    if (inputFile == NULL){
        printf("Erreur lors de l'ouverture du fichier d'entrée: %s\n",input_file_path);
        return;
    }

    //fichier de sortie 
    FILE *outputFile;
    outputFile = fopen(output_file_path,"w");
    


    char *ligne = NULL;
    size_t taille = 0;
    printf("Génération de la table T3C\n");
    while ((getline(&ligne, &taille, inputFile)) != -1) {
        //on supprime le caractères de fin de ligne 
        size_t len = strlen(ligne);
        if (len > 0 && ligne[len-1] == '\n') {
            ligne[len-1] = '\0';
        }
        if(strlen(ligne) > 0){
            if(strcmp(algorithm, "SHA512") == 0){
                char hash[SHA512_DIGEST_LENGTH * 2 + 1];
                get_hash_sha512(ligne, hash);
                fprintf(outputFile,"%s:%s\n",ligne,hash);
            }else if(strcmp(algorithm, "SHA384") == 0){
                char hash[SHA384_DIGEST_LENGTH * 2 + 1];
                get_hash_sha384(ligne, hash);
                fprintf(outputFile,"%s:%s\n",ligne,hash);
            }else if(strcmp(algorithm, "SHA256") == 0){
                char hash[SHA256_DIGEST_LENGTH * 2 + 1];
                get_hash_sha256(ligne, hash);
                fprintf(outputFile,"%s:%s\n",ligne,hash);
            }else if(strcmp(algorithm, "SHA224") == 0){
                char hash[SHA224_DIGEST_LENGTH * 2 + 1];
                get_hash_sha224(ligne, hash);
                fprintf(outputFile,"%s:%s\n",ligne,hash);
            }else if(strcmp(algorithm, "MD5") == 0){
                char hash[MD5_DIGEST_LENGTH * 2 + 1];
                get_hash_md5(ligne, hash);
                fprintf(outputFile,"%s:%s\n",ligne,hash);
            }else{
                printf("Algorithme inconnu: %s. \nAuthorisée: SHA512, SHA384, SHA256, SHA224, MD5.",algorithm);
                exit(1);
            }
        }
        
        
    }
    printf("Table T3C générée avec succès.\n");
    free(ligne);
    fclose(inputFile);
    fclose(outputFile);
}