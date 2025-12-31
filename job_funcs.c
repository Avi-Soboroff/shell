#include "helper_shell.h"

//prints all fields of job struct. This function is used for debugging other functions of the job struct
//uses helper function check if string fields of struct are NULL. If the pid of the child is <= 0, print it just as 0
// or -2, or whatever negative number it is without the leading #. 
void print_job(job_t *job){
    if (job == NULL){
        return;
    }
    printf("job {\n");
    printf("   .jobname       = '%s'\n", strnull(job->jobname));
    if (job->pid <= 0){
        printf("   .pid           = %d\n", job->pid);
    }
    else{
        printf("   .pid           = #%d\n", job->pid);
    }
    printf("   .retval        = %d\n", job->retval);
    printf("   .condition     = %s\n", job_condition_str(job));
    printf("   .output_file   = %s\n", strnull(job->output_file));
    printf("   .input_file    = %s\n", strnull(job->input_file));
    //even through this field is type char, prints out integer value of char, which is 0 or 1 for this particular field
    printf("   .is_background = %d\n", job->is_background);
    printf("   .argc          = %d\n", job->argc);
    printf("   .argv[] = {\n");
    for (int i = 0; i < job->argc; i++){
        printf("      [ %d] = %s\n", i, job->argv[i]);
    }
    printf("   }\n");
    printf("}\n");
}

//creates a new job based on the argv paramter. Returns NULL indicating error when no argument is passed. 
//Allocates heap memory for a job_t struct and creates heap copies of argv[] via string duplication. The
// initial condition of the job is INIT with -1 for its pid and retval. 
job_t *new_job(char *argv[]){
    if (argv == NULL){
        return NULL;
    }
    job_t *job = malloc(sizeof(job_t));
    job->pid = -1;
    job->retval = -1;
    job->condition = 1;
    job->output_file = NULL;
    job->input_file = NULL;
    job->is_background = 0;
    int i = 0;
    while (argv[i] != NULL && i < MAX_ARGS){
        job->argv[i] = strdup(argv[i]);
        i++;
    }
    job->argv[i] = NULL;
    job->argc = i;
    strncpy(job->jobname, job->argv[0], MAX_LINE);
    return job;
}

//deallocates all strings in argv field. then deallocates input and output files. Then deallocates structure itself
void free_job(job_t *job){
    for (int i = 0; i < job->argc; i++){
        free(job->argv[i]);
    }
    if (job->input_file != NULL){
        free(job->input_file);
    }
    if (job->output_file != NULL){
        free(job->output_file);
    }
    free(job);
}