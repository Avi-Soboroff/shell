#include "helper_shell.h"

int main(int argc, char *argv[]){
    int echo = 0;                                
    if(argc > 1 && strcmp("--echo",argv[1])==0) { 
        echo=1;
    }

    shell_t shell;
    init_shell(&shell);
    char line[1024];
    char *tokens[255]; //array for tokens/commands
    int ntok; //number of tokens in command line
    char *cmd;

    while(1){
        update_all_shell(&shell);
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
        tokenize_string(line, tokens, &ntok);
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
        else if (strcmp("jobs", cmd)==0){
            print_job_shell(&shell);
        }
        else if (strcmp("pause", cmd)==0){
            double time = atof(tokens[1]);
            pause_for(time);
            printf("pausing for %.3f seconds\n", time);
        }
        else if (strcmp("tokens", cmd)==0){
            printf("%d tokens in command line\n", ntok);
            for (int i = 0; i < ntok; i++){
                printf("tokens[%d]: %s\n", i, tokens[i]);
            }
        }
        else if (strcmp("wait", cmd)==0){
            if (ntok < 2){
                printf("ERROR: No job '%s' to wait for\n", tokens[1]);
                continue;
            }
            int jobnum = atoi(tokens[1]);
            wait_one_shell(&shell, jobnum);
        }
        else {
            job_t *job = new_job(tokens); //new job created with the amount of tokens/arguments present
            int job_index = add_job_shell(&shell, job);
            //check in case there isn't any more space to add a job, otherwise start that specific job
            if (job_index == -1){
                free_job(job);
            }
            else { 
                start_job_shell(&shell, job_index);
                if (!job->is_background){
                    update_one_shell(&shell, job_index);
                }
            }
        }
    }
    free_jobs_shell(&shell);
    return 0;
}