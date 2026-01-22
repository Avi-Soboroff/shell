#include "helper_shell.h"

int main() {
    char *args[] = {
      "ascii","x",">","output.txt", NULL
    };
    job_t *job = new_job(args);
    print_job(job);
}