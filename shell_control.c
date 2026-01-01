#include "helper_shell.h"

//sets all fields of shell struct to 0 or NULL
void init_shell(shell_t *shell){
    for (int i = 0; i < MAX_JOBS; i++){
        shell->jobs[i] = NULL;
    }
    shell->job_count = 0;
}

//prints all non-NULL jobs in shell
void print_job_shell(shell_t *shell){
    int i = 0;
    while (shell->jobs[i] != NULL && i < MAX_JOBS){
        printf("[%d] %s\n", i, shell->jobs[i]->jobname);
        i++;
    }
    printf("%d total jobs\n", i);
}

//adds a job to job array. find first NULL spot and put job in. checks to make sure array isnt full. 
//Returns the index in the jobs array (job number) where the new job is added. If the jobs array is full, prints an error message
//and returns -1.
int add_job_shell(shell_t *shell, job_t *job){
    for (int i = 0; i < MAX_JOBS; i++){
        if (shell->jobs[i] == NULL){
            shell->jobs[i] = job;
            shell->job_count++;
            return i;
        }
    }
    printf("ERROR: Max jobs reached. No more can be allowed!!");
    return -1;
}

//checks if job exits. If not then error, otherwise deallocates that job from memory, and sets it to NULL.
//Also decrements job_count
int remove_job_shell(shell_t *shell, int idx){
    if (shell->jobs[idx] == NULL){
        printf("No such job exits");
        return -1;
    }
    free_job(shell->jobs[idx]);
    shell->jobs[idx] = NULL;
    shell->job_count--;
    return 0;
}

//start a specific job from list
void start_job_shell(shell_t *shell, int jobnum){
    printf("=== JOB %d STARTING: %s ===\n", jobnum, shell->jobs[jobnum]->jobname);
    start_job(shell->jobs[jobnum]);
}


void free_jobs_shell(shell_t *shell){
    if (shell == NULL){
        return;
    }
    for (int i = 0; i < MAX_JOBS; i++){
        if (shell->jobs[i] != NULL){
            free_job(shell->jobs[i]);
            shell->jobs[i] = NULL;
        }
    }
    shell->job_count = 0;
}

void update_one_shell(shell_t *shell, int jobnum){
    job_t *job = shell->jobs[jobnum];
    if (job == NULL){
        return;
    }
    int update = update_job_status(job);
    if (update){
        printf("=== JOB %d COMPLETED %s [#%d]: %s ===\n", jobnum, job->jobname, job->pid, job_condition_str(job));
        remove_job_shell(shell, jobnum);
    }
}

void update_all_shell(shell_t *shell){
    for (int i = 0; i < MAX_JOBS; i++){
        update_one_shell(shell, i);
    }
}

void wait_one_shell(shell_t *shell, int jobnum){
    if (jobnum < 0 || jobnum > MAX_JOBS || shell->jobs[jobnum] == NULL){
        printf("ERROR: No job '%d' to wait for\n", jobnum);
        return;
    }
    job_t *job = shell->jobs[jobnum];
    job->is_background = 0;
    update_one_shell(shell, jobnum);
}