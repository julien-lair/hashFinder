#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

typedef struct Node_Tree_{
    unsigned long value;
    char* clair;
    char* hash;
    struct Node_Tree_* leftChild;
    struct Node_Tree_* rightChild;
} Node_Tree;

unsigned long hash_to_unique_value(char* hash){
    unsigned long result = 0;
    for (int i = 0; i < strlen(hash); i++){
        result = result * 31 + hash[i];
    }
    return result;
}

void insert_node(Node_Tree** actualNode, Node_Tree* new_node){
   if((*actualNode) == NULL ){
    //on est sur une feuille 
    //on ajoute la valeur à la place du noeud NULL
    *actualNode = new_node;

    }else{
    //si on est pas sur une feuille on regarde de quelle coté au descend l'arbre 
        if(new_node->value < (*actualNode)->value){
            //on part vers la gauche
            insert_node(&(*actualNode)->leftChild,new_node);//on donne l'adresse du pointeur 
            
        }else if(new_node->value > (*actualNode)->value){
            //on part vers la droite
            insert_node(&(*actualNode)->rightChild,new_node);
        }else{
            //même valeur, colision de détecter 
            printf("Attention: collision ...\n");
        }
   }
}
void show_tree(Node_Tree* node){
    if(node->leftChild != NULL){
        show_tree(node->leftChild);
    }
    if(node->rightChild != NULL){
        show_tree(node->rightChild);
    }
    //printf("val: %lu, claire: %s\n",node->value, node->clair);
}
Node_Tree* create_tree(char* input_file_path){
    //printf("je créer l'arbre\n");
    Node_Tree* rootNode = NULL;

    FILE* t3cFile;
    t3cFile = fopen(input_file_path, "r");
    if(t3cFile == NULL){
        printf("Erreur : le fihcier %s n'a pas été trouvé.",input_file_path);
    }


    //on parcour chaques lignes du fichier
    char *ligne = NULL;
    size_t taille = 0;
    while ((getline(&ligne, &taille, t3cFile)) != -1) {
        /*
        char *clair = strtok(ligne, ":");
        char *hash  = strtok(NULL, ":"); 
        */

        ligne[strcspn(ligne, "\n")] = '\0'; //on supprime le caractère retour à la ligne
        
        char *last_colon = strrchr(ligne, ':'); //on récupère la dernière occurence de : sur la ligne
        *last_colon = '\0'; //remplace le dernier : par un caractère null
        char *clair = ligne; 
        char *hash  = last_colon + 1;

        unsigned long valueOfNode = hash_to_unique_value(hash);
        //on init notre nouveau node
        Node_Tree* nodeAInserer = malloc(sizeof(Node_Tree));
        nodeAInserer->clair = strdup(clair);
        nodeAInserer->hash = strdup(hash);
        nodeAInserer->value = valueOfNode;
        nodeAInserer->leftChild = NULL;
        nodeAInserer->rightChild = NULL;

        //on insère. le nouveau node 
        insert_node(&rootNode,nodeAInserer);
        //printf("%s -> %lu\n",hash,valueOfNode);
    }
    //show_tree(rootNode);
    return rootNode;
}


Node_Tree* find_node(char* hash, Node_Tree* actualNode){
    unsigned long valueOfNode = hash_to_unique_value(hash);
    //printf("%s -> %lu\n",hash,valueOfNode);

    if(actualNode == NULL){
        //on est en dessous d'une feuille (pas trouvé la valeur)
        return NULL;
    }else if(actualNode->value == valueOfNode){
        return actualNode;
    }else if(valueOfNode < actualNode->value){
        return find_node(hash, actualNode->leftChild);
    }else if(valueOfNode > actualNode->value){
        return find_node(hash, actualNode->rightChild);
    }
    return NULL;

}