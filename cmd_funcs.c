#include "helper_shell.h"

// Allocates space in heap for a command. Initializes process id to -1
// and sets the command name to the first string in the list passed as an 
// argument. Allocates space in newly created struct for each command passed in 
// the line. 
cmd_t *new_cmd(char *cmd_list[]){
    cmd_t *cmd = malloc(sizeof(cmd_t));
    if (cmd == NULL){
        return NULL;
    }
    cmd->p_id = -1;
    strncpy(cmd->cmd_name, cmd_list[0], MAXLINE);
    cmd->cmd_name[MAXLINE-1] = '\0'; // NULL terminate end of command name
    int i = 0;
    while (cmd_list[i] != NULL && i < MAXCMDS){
        cmd->all_cmds[i] = strdup(cmd_list[i]);
        i++;
    }
    cmd->all_cmds[i] = NULL; // NULL terminate the array for execvp
    cmd->cmd_count = i;
    return cmd;
}

// First frees all commands in list and then the struct itself
void cmd_free(cmd_t *cmd){
    for (int i = 0; i < cmd->cmd_count; i++){
        free(cmd->all_cmds[i]);
    }
    free(cmd);
}

void cmd_start(cmd_t *cmd){
    pid_t process = fork();
    if (process < 0){ //error in duplicating a process
        return;
    }

    if (process == 0){ //when we have a child process, we exec to execute that command
        umask(0);
        execvp(cmd->all_cmds[0], cmd->all_cmds);
        printf("ERROR: cmd failed to exec: No such file or directory\n");
        exit(0);
    }
    if (process > 0){
        cmd->p_id = process;
    }
}