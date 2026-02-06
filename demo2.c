#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        //child
        printf("Child PID = %d exiting...\n", getpid());
        exit(0);
    } else {
      //parent
        printf("Parent PID = %d\n", getpid());
        printf("Child created, not calling wait() yet...\n");

        sleep(15);   // Zombie exists during this time

        printf("\nParent calling wait() → Zombie cleanup\n");
        wait(NULL);  // cleanup happens here

        sleep(10);   // confirm zombie is gone
    }

    return 0;
}
