#include "helper_shell.c"

int main(int argc, char *argv[]){
    int echo = 0;                                
    if(argc > 1 && strcmp("--echo",argv[1])==0) { 
        echo=1;
    }

    char line[1024];
    char *tokens[255]; //array for tokens/commands
    int ntok;

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
    }

    return 0;
}