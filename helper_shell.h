#include <stdio.h>
#include <string.h> 
#include <Kernel/sys/_types/_pid_t.h>

#define MAXCMDS 255
#define MAXLINE 1024

//struct which holds the value of each command
typedef struct {
    pid_t p_id;
    char cmd_name[MAXLINE];
} cmd_t;

typedef struct {
    cmd_t *cmd;
    node_t *head; //pointer to first node in list
    int size;
} cmd_list;

typedef struct {
    node_t *head;
    node_t *tail;
} node_t;

//the head of first node in list set to NULL; tail of last element is set to NULL

//functions for helper_shell.c
void print_help();
void tokenize_str(char line[], char *tokens[], int *ntok);