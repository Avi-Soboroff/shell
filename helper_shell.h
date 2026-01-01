#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// #include <math.h>       // for fmod() in util

// #define eprintf(...) fprintf (stderr, __VA_ARGS__)


// compile time constants for sizes
#define BUFSIZE 1024            // size of read/write buffers
#define MAX_ARGS 255             // max number of arguments
#define MAX_LINE 1024           // maximum length of input lines
#define MAX_JOBS 256            // maximum number of active commands in shell


// // specific code for certain failure types
// #define FAIL_EXEC 128           
// #define FAIL_OUTP 129           // numeric code indicating a failure due to output redirection
// #define FAIL_INPT 130           // numeric code indicating a failure due to input redirection

// numeric condition numbers associated with job states, possibly
// better as an enum but it matters very little
#define JOBCOND_UNSET 0                // not set, likely 0 due to memory state
#define JOBCOND_INIT  1                // just created, not started yet
#define JOBCOND_RUN   2                // forked / exec()'d and running
#define JOBCOND_EXIT  3                // exited normally, retval has return value
#define JOBCOND_FAIL_EXEC  128         // numeric code indicating a failure to exec() a command
#define JOBCOND_FAIL_OUTP  129         // numeric code indicating a failure due to output redirection
#define JOBCOND_FAIL_INPT  130         // numeric code indicating a failure due to input redirection
#define JOBCOND_FAIL_OTHER 131         // numeric code indicating a failure for other undiagnosed reasons


// job_t: struct to represent a running job/child process.
typedef struct {
  char   jobname[MAX_LINE];        // name of command like "ls" or "gcc"
  char  *argv[MAX_ARGS+1];          // argv for running child, NULL terminated
  int    argc;                     // number of elements on command line
  pid_t  pid;                      // PID of child
  int    retval;                   // return value of child, -1 if not finished
  int    condition;                // one of the JOBCOND_xxx values whic indicates state of job
  char  *output_file;              // name of output file or NULL if stdout
  char  *input_file;               // name of input file or NULL if stdin
  char   is_background;            // 1 for background job (& on command line), 0 otherwise
} job_t;

// shell_t: struct for tracking state of shell
typedef struct {                
  job_t *jobs[MAX_JOBS];         // array of pointers to job_t structs; may have NULLs internally
  int job_count;                 // count of non-null job_t entries
} shell_t;


// helper_shell.c: PROVIDED UTILITY FUNCTIONS
void Dprintf(const char* format, ...);
char *strnull(char *str);
char *job_condition_str(job_t *job);
void tokenize_string(char input[], char *tokens[], int *ntok); 
void pause_for(double secs);
void array_shift(char *strs[], int delpos, int maxlen);
void print_help();

// shell_job.c
job_t *new_job(char *argv[]);
void free_job(job_t *job);
void print_job(job_t *job);
int update_job_status(job_t *job);
void start_job(job_t *job);

// shell_control.c
void init_shell(shell_t *shell);
int add_job_shell(shell_t *shell, job_t *job);
int remove_job_shell(shell_t *shell, int idx);
void start_job_shell(shell_t *shell, int jobnum);
void print_job_shell(shell_t *shell);
void free_jobs_shell(shell_t *shell);
void update_one_shell(shell_t *shell, int jobnum);
void update_all_shell(shell_t *shell);
void wait_one_shell(shell_t *shell, int jobnum);

