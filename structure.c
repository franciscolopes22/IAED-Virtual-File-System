/*
// Created by Francisco Lopes 99220 on 5/14/2021.
*/

#include "structure.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief strcopy Reserves memory for the dest pointer and copies the value to it.
 * @param dest Destination string where the value is stored
 * @param value Value to be copied to the destination
 * @return Returns the new pointer for dest. Return NULL if there was a problem reserving memory.
 */
char *strcopy(char ** dest, char * value) {
    if(*dest != NULL) {
        free(*dest);
    }
    if(value == NULL) {
        *dest = NULL;
        return NULL;
    }

    *dest = (char *) malloc(sizeof(char) * (strlen(value) + 1));
    if(*dest == NULL) {
        return NULL; /* Out of memory */
    }
    strcpy(*dest, value);
    return *dest;
}



/**
 * @brief newNode Creates a new Node and assigns it the name and value.
 * @param name String of the name to be stored as name of the directory/node.
 * @param value String of the value to be stored as name of the directory/node.
 * @return Returns the new pointer for the node created.
 */
struct node* newNode(char * name, char * value){
    /* Allocate memory for new node */
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->name = NULL;
    node->value = NULL;

    /* Assign name and value to this node */
    strcopy(&node->name, name);
    strcopy(&node->value, value);


    /* Initialize child and sibling as NULL */
    node->path = NULL;
    node->child = NULL;
    node->sibling = NULL;
    node->childSorted = NULL;
    node->siblingSorted = NULL;

    return node;
}

/**
* @brief insertChild Inserts node child, without setting the value, and inserting it in order.
* @param root Root node.
* @param name String of the name to be stored as name of the directory/node.
* @return Returns the new pointer for the node created.
*/
struct node* insertChild(struct node* root, char * name){
    struct node* x = root->child;
    struct node* prev = root;
    struct node* new = newNode(name, NULL);

    if(new == NULL) {
        return NULL; /* out of memory */
    }

    /* No children, create the first node */
    if(x == NULL) {
        root->child = new;
        root->childSorted = new;
        return root->child;
    }

    /* Save sibling at the end to be sorted by creation */
    while(x != NULL){
        if(strcmp(x->name, name) == 0){
            freeNode(new);  /* Not need, free */
            return x;
        }
        prev = x;
        x = x->sibling;
    }
    prev->sibling = new;

    /* Insert the new node as child of root, but sorted by name */
    x = root->childSorted;
    prev = root;
    while(x != NULL) {
        if(strcmp(x->name, name) > 0) {
            /* should be added before */
            if(prev == root) {
                struct node* aux = root->childSorted;
                root->childSorted = new;
                new->siblingSorted = aux;
            }
            else {
                struct node* aux = prev->siblingSorted;
                prev->siblingSorted= new;
                new->siblingSorted = aux;
            }
            return new;
        }
        prev = x;
        x = x->siblingSorted;
    }
    prev->siblingSorted = new; /* Added at the end sorted */

    return new;
}


/**
* @brief insertValue Inserts/Updates value and path in node.
* @param node Node you wish to insert/update Value.
* @param path Path of the node.
* @return Returns the new pointer for the node updated. Returns Null if Out of memory.
*/
struct node* insertValue(struct node* node, char * value, char *path) {
    char *p = strcopy(&node->value, value);
    if(p == NULL) {
        return NULL; /* Out of memory */
    }
    p = strcopy(&node->path, path);
    if(p == NULL) {
        return NULL; /* Out of memory */
    }
    return node;
}

/**
* @brief existsSibling Searches for sibling.
* @param node Node you wish to search in.
* @param name Name you wish to search for.
* @return Returns the new pointer for the node if found. Returns Null if not found.
*/
struct node* existsSibling(struct node* node, char * name){
    struct node* x = node;

    while(x != NULL){
        if(strcmp(x->name, name) == 0){
            return x;
        }
        x = x->sibling;
    }
    return NULL;
}

/**
* @brief freeNode Frees node memory.
* @param root Node you wish to free memory.
* @return Returns Null.
*/
void freeNode(struct node *node) {
    if(node == NULL) { /*No memory*/
        return;
    }
    free(node);
}

/**
* @brief deleteNode Deletes node/directory and all sub-directories/children and siblings, and updates sorted order.
* @param root Node you wish to delete.
* @param parent Father of the Node you wish to delete.
* @return Returns Null.
*/
void deleteNode(struct node *node, struct node *parent) {
    struct node *x = node->child;
    struct node *sibling = node->sibling;
    struct node *siblingSorted = node->siblingSorted;
    struct node *prev = NULL;

    /* Free children */
    while(x != NULL) {
        struct node *aux = x;
        x = x->sibling;
        freeNode(aux);
    }

    /* BY creation */
    if(parent->child == node) {
        parent->child = sibling;
    }
    else {
        prev = parent->child;
        while(prev->sibling != node) {
            prev = prev->sibling;
        }
        prev->sibling = sibling;
    }

    /* By sorted  */
    if(parent->childSorted == node) {
        parent->childSorted = siblingSorted;
    }
    else {
        prev = parent->childSorted;
        while(prev->siblingSorted != node) {
            prev = prev->siblingSorted;
        }
        prev->siblingSorted = siblingSorted;
    }

    free(node);
}
