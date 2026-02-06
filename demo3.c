#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t c1, c2;

    c1 = fork();

    if (c1 == 0) {
        //zombie
        printf("Child 1 (Zombie) PID = %d\n", getpid());
        printf("Child 1 exiting...\n");
        exit(0);
    }

    c2 = fork();

    if (c2 == 0) {
        //orphan
        printf("Child 2 (Orphan) PID = %d\n", getpid());
        printf("Child 2 sleeping...\n");
        sleep(20);
        printf("Child 2 Parent PID after orphan = %d\n", getppid());
        exit(0);
    }

    //parent
    printf("Parent PID = %d\n", getpid());
    printf("Not calling wait() → Child 1 becomes ZOMBIE\n");
    printf("Parent exiting → Child 2 becomes ORPHAN\n");

    sleep(10);   // time to observe zombie
    exit(0);
}
