#include <stdio.h>
#include <string.h>

#define MAXCMDS 255 

void print_help(){
  char *helpstr = "\
SHELLAC COMMANDS\n\
help               : show this message\n\
exit               : exit the program\n\
jobs               : list all background jobs that are currently running\n\
pause <secs>       : pause for the given number of seconds, fractional values supported\n\
wait <jobnum>      : wait for given background job to finish, error if no such job is present\n\
tokens [arg1] ...  : print out all the tokens on this input line to see how they apper\n\
command [arg1] ... : Non-built-in is run as a job\n\
";
  printf("%s",helpstr);
}

//splits up the input string and places each token into the tokens array
void tokenize_str(char line[], char *tokens[], int *ntok){
    int i = 0;
    //gets the first token in the array and loops through input until the end is reached
    char *tok = strtok(line, " \n"); 
    while (tok != NULL && i < MAXCMDS){
        tokens[i] = tok;
        i++;
        tok = strtok(NULL, " \n");
    }
    tokens[i] = NULL;
    *ntok = i;
    return;
}