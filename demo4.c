#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <time.h>

void set_cpu(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
}

long long run_even_numbers() {
    long long sum = 0;
    for (int i = 0; i <= 10000000; i += 2) {  // large number for measurable time
        sum += i;
    }
    return sum;
}

long long run_odd_numbers() {
    long long sum = 0;
    for (int i = 1; i <= 10000000; i += 2) {
        sum += i;
    }
    return sum;
}

int main() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        // Uncomment below to test WITH affinity
        set_cpu(1);

        long long odd_sum = run_odd_numbers();
        printf("Child sum (odd) = %lld\n", odd_sum);
    } else {
        // Parent process
        // Uncomment below to test WITH affinity
        set_cpu(0);

        long long even_sum = run_even_numbers();
        printf("Parent sum (even) = %lld\n", even_sum);

        wait(NULL);  // wait for child to finish
        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken = (end.tv_sec - start.tv_sec) + 
                            (end.tv_nsec - start.tv_nsec)/1e9;
        printf("\nTotal Execution Time = %.6f seconds\n", time_taken);
    }

    return 0;
}
