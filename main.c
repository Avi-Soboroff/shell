#include "helper_shell.h"

int main(int argc, char *argv[]){
    int echo = 0;                                
    if(argc > 1 && strcmp("--echo",argv[1])==0) { 
        echo=1;
    }

    cmd_list list;
    list_init(&list);
    char line[1024];
    char *tokens[255]; //array for tokens/commands
    int ntok;
    char *cmd;

    while(1){
        printf("(shell) ");
        fflush(stdout);
        char *input = fgets(line, 1024, stdin); //reads a line from the shell
        if (input == NULL){
            printf("\nEnd of input");
            break;
        }

        if (echo){
            printf("%s", line);
        }
        tokenize_str(line, tokens, &ntok);
        if (ntok == 0){
            continue;
        }
        
        cmd = tokens[0];
        if (strcmp("help", cmd)==0){
            print_help();
        }
        else if (strcmp("exit", cmd)==0){
            break;
        }
        else {
            cmd_t *cmd = new_cmd(tokens);
            int adding_cmds = add_to_list(&list, cmd);
        }
    }

    return 0;
}