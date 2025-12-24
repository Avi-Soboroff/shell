#include <stdio.h>
#include <string.h> 

#define MAXCMDS 255


//functions for helper_shell.c
void print_help();
void tokenize_str(char line[], char *tokens[], int *ntok);