#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <stdlib.h>

#define MAXCMDS 255
#define MAXLINE 1024

typedef struct node_struct node_t;

//struct which holds the value of each command
typedef struct {
    pid_t p_id; //process id
    int cmd_count;
    char cmd_name[MAXLINE]; //cmd name
    char *all_cmds[MAXCMDS+1]; //list of all commands
} cmd_t;

struct node {
    cmd_t cmd;
    node_t *next;
};

typedef struct {
    node_t *head;
    node_t *tail;
    int size;
} cmd_list;

//the head of first node in list set to NULL; tail of last element is set to NULL

//functions for helper_shell.c
void print_help();
void tokenize_str(char line[], char *tokens[], int *ntok);

//functiond for cmd_funcs.c
cmd_t *new_cmd(char *argv[]);
void cmd_free(cmd_t *cmd);
void cmd_start(cmd_t *cmd);