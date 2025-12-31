#include "helper_shell.h"

int main() {
    char *args[] = {
      "seq", "0", "5", "30", NULL,
    };
    job_t *job = new_job(args);
    print_job(job);
    start_job(job);
    wait(NULL);  // ensure child finishes with any output flushed
    print_job(job);
    free_job(job);
    return 0;
}