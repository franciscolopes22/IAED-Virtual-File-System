/*
// Created by Francisco Lopes 99220 on 5/14/2021.
*/

#include "commands.h"
#include "structure.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
* @brief help Prints all the commands available to use.
* @return Returns void.
*/
void help() {
    printf("help: Imprime os comandos disponíveis.\n"
           "quit: Termina o programa.\n"
           "set: Adiciona ou modifica o valor a armazenar.\n"
           "print: Imprime todos os caminhos e valores.\n"
           "find: Imprime o valor armazenado.\n"
           "list: Lista todos os componentes imediatos de um sub-caminho.\n"
           "search: Procura o caminho dado um valor.\n"
           "delete: Apaga um caminho e todos os subcaminhos.\n");
}

/**
* @brief quit Quits programme.
* @return Returns void.
*/
void quit(struct node *root) {
    if(root == NULL) {
        return;
    }
    freeNode(root);
    exit(0);
}


/**
* @brief fixPath Removes extra '/', assures there is a '/' at the beginning and no '/' at the end.
* @param root Node you wish to delete.
* @param parent Father of the Node you wish to delete.
* @return Returns char pointer of fixed path.
*/
char * fixPath(char *path, size_t size) {
    char *new = (char*) malloc(sizeof(char) * (size + 1));
    char *name;

    new[0] = '\0';
    name = strtok(path, "/");
    while(name != NULL) {
        strcat(new, "/");
        strcat(new, name);
        name = strtok(NULL, "/");
    }
    return new;
}


/**
* @brief searchNode Search for a path in tree structure. If the path is NULL, returns the root node.
* @param root Root node.
* @param path Path you wish to search.
* @param parent Father of the Node you found.
* @return If the path is NULL, returns the root node, If the path is not valid it return NULL.
*/
struct node *searchNode(struct node *root, char *path, struct node **parent) {
    struct node *x = root;
    char *name = NULL;

    if(path == NULL) {
        /* Root node */
        if(parent != NULL) {
            *parent = NULL;
        }
        return root;
    }

    /* search for other node */
    name = strtok(path, "/");
    while(name != NULL) {
        if(parent != NULL) {
            *parent = x;
        }
        x = existsSibling(x->child, name);
        if(x == NULL) {
            return NULL;
        }
        name = strtok(NULL, "/");
    }
    return x;
}

/**
* @brief set Adds of changes the value to be stored.
* @param root Root node.
* @return Returns 0 if invalid, 1 if success, -1 if out of memory.
*/
int set(struct node* root) {
    char * path = NULL;
    char * originalPath = NULL;
    char * value = NULL;
    char * name = NULL;
    char * p = NULL;
    struct node* temp = root;
    size_t pathSize = 0;

    path = strtok(NULL, " \t");
    value = strtok(NULL, "\n");
    strcopy(&originalPath, path);

    name = strtok(path, "/");
    while(name != NULL) {
        pathSize += strlen(name) + 1;
        temp = insertChild(temp, name);
        if(temp == NULL) { /* out of memory */
            free(originalPath);
            return -1;
        }
        name = strtok(NULL, "/");
    }

    if(temp == root) {
        return 0; /* The path is invalid */
    }

    p = fixPath(originalPath, pathSize);
    free(originalPath);
    if(p == NULL) {
        return -1;
    }

    /* Update the value in the last child */
    if(insertValue(temp, value, p) == NULL) {
        free(p);
        return -1;
    }
    return 0;
}



/**
* @brief print Prints all paths and values in depth and creation order.
* @param root Root node.
* @return Returns void.
*/
void print(struct node *root) {
    struct node *temp;

    if(root == NULL) {
        return;
    }

    temp = root->child;
    while(temp != NULL) {
        if(temp->value != NULL) {
            printf("%s %s\n", temp->path, temp->value);
        }
        print(temp);
        temp = temp->sibling;
    }
}

/**
* @brief print Prints all directory names alphabetically
* @param root Root node.
* @return Returns void.
*/
void printSorted(struct node *root) {
    struct node *temp;

    if(root == NULL) {
        return;
    }

    temp = root->childSorted;
    while(temp != NULL) {
        print(temp);
        if(temp->value != NULL) {
            printf("%s\n", temp->name);
        }
        temp = temp->siblingSorted;
    }
}



/**
* @brief find Prints the stored value in a path.
* @param root Root node.
* @return Returns void.
*/

void find(struct node *root) {
    char *path = NULL;
    struct node *x = NULL;

    if(root == NULL) {
        return;
    }
    path = strtok(NULL, "\n");
    x = searchNode(root, path, NULL);

    if(x != NULL) {
        if(x->value != NULL)
            printf("%s\n", x->value);
        else
            printf("no data\n");
    }
    else {
        printf("not found\n");
    }
}

/**
* @brief list Lists all the immediate components in a sub-dir.
* @param root Root node.
* @return Returns void.
*/
void list(struct node *root) {
    char *path = NULL;
    struct node *x = NULL;

    if(root == NULL) {
        return;
    }

    path = strtok(NULL, "\n");
    x = searchNode(root, path, NULL);

    if(x != NULL) {
        printSorted(x);
    }
    else {
         printf("not found\n");
    }
}
/**
* @brief searchAux search function aux, updates prt if match found.
* @param root Root node.
* @param value Value you wish to search.
* @param ptr Pointer to string path, to update in case of match.
* @return Returns void.
*/
void searchAux(struct node *root, char * value, char ** ptr) {
    struct node *temp;
    if(root == NULL) { /* No memory*/
        return;
    }

    temp = root->child;
    while(temp != NULL) {
        if(temp->value != NULL && strcmp(temp->value, value) == 0) {
            if (ptr != NULL)
            strcopy(ptr, temp->path);
        }
        searchAux(temp, value, ptr);
        temp = temp->sibling;
    }
}

/**
* @brief search Searches for the path of a value.
* @param root Root node.
* @return Returns void.
*/
void search(struct node *root) {
    char *value = NULL;
    char *p = NULL;
    char **ptr = &p;


    value = strtok(NULL, "\n");

    searchAux(root, value, ptr);
    if (p != NULL) {
        printf("%s\n", p);
    return;
    }
    printf("not found\n");

}

/**
* @brief delete Deletes every path of a sub-path.
* @param root Root node.
* @return Returns void.
*/
void delete(struct node *root) {
    char *path = NULL;
    struct node *x = NULL;
    struct node *parent = NULL;

    if(root == NULL) {
        return;
    }

    path = strtok(NULL, "\n");
    x = searchNode(root, path, &parent);

    if(x != NULL) {
        deleteNode(x, parent);
    }
    else {
        printf("not found\n");
    }


}
