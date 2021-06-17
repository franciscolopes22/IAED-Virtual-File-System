/*
// Created by Francisco Lopes 99220 on 5/14/2021.
*/

#ifndef PROJETO_STRUCTURE_H
#define PROJETO_STRUCTURE_H


struct node {
    char * name;
    char * value;
    char * path;
    struct node* child;
    struct node* childSorted;
    struct node* sibling;
    struct node* siblingSorted;
};


char *strcopy(char ** dest, char *value);
struct node* newNode(char * name, char * value);
struct node* insertChild(struct node* root, char * name);
struct node* insertValue(struct node* node, char * value, char *path);
struct node* existsSibling(struct node* node, char * name);
void freeNode(struct node* node);
void deleteNode(struct node *node, struct node *parent);




#endif
