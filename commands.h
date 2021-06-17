/*
// Created by Francisco Lopes 99220 on 5/14/2021.
*/

#ifndef PROJETO_COMMANDS_H
#define PROJETO_COMMANDS_H
#include "structure.h"


/* Commands */
void help(void);
void quit(struct node* root);
int set(struct node* root);
void print(struct node* root);
void find(struct node *root);
void list(struct node *root);
void search(struct node *root);
void searchAux(struct node *root, char * value, char ** ptr);
void delete(struct node *root);



#endif
