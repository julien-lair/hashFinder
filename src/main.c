#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "generate.c"
#include "lookup.c"

int main(int argc,char** argv){
    //./hashfinder -g -f data/dictionnaire.txt -o data/table.t3c -algo sha256
    //./hashfinder -l -f data/table.t3c
    //echo "5d41402abc4b2a76b9719d911017c592" | ./hashfinder -l -f data/table.t3c
    //cat data/hashes.txt | ./hashfinder -l -f data/table.t3c
    bool generation_mode = false;
    bool lookup_mode = false;
    char* input_file = NULL;
    char* output_file = NULL;
    char* algorithm = "SHA256"; //algo par défault

    int i;
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i], "-g") == 0){
            generation_mode = true;
        }
        else if(strcmp(argv[i], "-f") == 0 && i + 1 < argc){
            input_file = argv[i+1];
            i++;
        }
        else if(strcmp(argv[i], "-o") == 0 && i + 1 < argc){
            output_file = argv[i+1];
            i++;
        }
        else if(strcmp(argv[i], "-algo") == 0 && i + 1 < argc){
            algorithm = argv[i+1];
            i++;
        }
        else if(strcmp(argv[i], "-l") == 0){
            lookup_mode = true;
        }
        else{
            printf("Argument inconnu: %s\n",argv[i]);
            return 1;
        }
    }
    if(generation_mode == true && lookup_mode == true){
        printf("Les modes -g et -l sont incompatibles.\n");
        return 1;
    }
    else if(generation_mode == true && input_file != NULL && output_file != NULL){
        generate_t3c(input_file, output_file, algorithm);
    }else if(lookup_mode == true && input_file != NULL){
        lookup_t3c(input_file);
    }else{
        printf("Usage pour la génération: ./hashfinder -g -f <fichier_entrée> -o <fichier_sortie> [-algo <algorithme>]\n");
        printf("Usage pour la recherche: ./hashfinder -l -f <fichier_table>\n");
        return 1;
    }
    
    return 0;

    

}