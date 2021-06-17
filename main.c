/*
// Created by Francisco Lopes 99220 on 5/14/2021.
*/

#include "commands.h"
#include "structure.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    char line[65535];
    char *command;
    struct node* root = newNode("", NULL);

    for(;;) { /* Ciclo infinito */
        fgets(line, 65535, stdin);
        line[strlen(line) - 1] = '\0'; /* remove \n */

        /* get the command */
        command = strtok(line, " \n");

        if(strcmp(command, "help") == 0){
            help();
        }
        else if(strcmp(command, "quit") == 0){
            quit(root);
            break; /* termina o ciclo */
        }
        else if(strcmp(command, "set") == 0){
            set(root);
        }
        else if(strcmp(command, "print") == 0){
            print(root);
        }
        else if(strcmp(command, "find") == 0){
            find(root);
        }
        else if(strcmp(command, "search") == 0){
            search(root);
        }
        else if(strcmp(command, "list") == 0){
            list(root);
        }
        else if(strcmp(command, "delete") == 0){
            delete(root);
        }
        else {
            /* Invalid Command */
        }
    }
    return 0;
}

