#include <stdio.h>
#include <stdlib.h>
#include "hash.c"

void generate_t3c(char* input_file_path, char* output_file_path, char* algorithm){
    // Générationd e la table T3C
    //fichier d'entré
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

    while ((getline(&ligne, &taille, inputFile)) != -1) {
        //on suppirme le carcateres de fin de ligne 
        size_t len = strlen(ligne);
        if (len > 0 && ligne[len-1] == '\n') {
            ligne[len-1] = '\0';
        }
        
        char hash[SHA256_DIGEST_LENGTH * 2 + 1];
        get_hash_sha256(ligne, hash);
        // printf("%s:%s\n",ligne,hash);
        //écrire dans le fichier de sortie
        fprintf(outputFile,"%s:%s\n",ligne,hash);
    }
    free(ligne);
    fclose(inputFile);
    fclose(outputFile);
}