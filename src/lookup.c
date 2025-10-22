#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arbreBinaire.c"

void lookup_t3c(char *input_file_path){
   
    Node_Tree* rootNode = create_tree(input_file_path);
   
    //on récupère l'entré utilisateur
    bool continue_while = true;
    printf("Entrez le hash pour obtenir sont claire\nTapez `exit` pour quitter\n");

    while(continue_while == true){
       char* user_entry = NULL;
       size_t len_user_entry = 0;
        if(getline(&user_entry, &len_user_entry, stdin) > 0){
            //on supprime le cracatere de fin 
            user_entry[strcspn(user_entry, "\n")] = '\0';
            //si l'utilisateur tape exit 
            if(strcmp(user_entry,"exit") == 0){
                exit(0);
            }
            Node_Tree* nodeFind = find_node(user_entry,rootNode);
            if(nodeFind == NULL){
                //pas trouvé
                printf("pas trouvé\n");
            }else{
                printf("--> %s\n",nodeFind->clair);
            }
        }
    }
    
}