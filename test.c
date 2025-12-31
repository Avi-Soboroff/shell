#include "helper_shell.h"

int main() {
    char *argv[] = {"ls", "-l", "/tmp", NULL};
    job_t *job = new_job(argv);
    print_job(job);
    // free_job(job);
    return 0;
}