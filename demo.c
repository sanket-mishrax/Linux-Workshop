#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

long long factorial(int n) {
    long long f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

int is_prime(long long x) {
    if (x < 2) return 0;
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int n;
    long long fact;
    long long factors[1000];
    int count = 0;

    printf("Enter a number (<=10 recommended): ");
    scanf("%d", &n);

    fact = factorial(n);
    printf("\nParent: Factorial of %d is %lld\n", n, fact);

    /* Find factors of factorial */
    for (long long i = 1; i <= fact; i++) {
        if (fact % i == 0) {
            factors[count++] = i;
        }
    }

    pid_t child1 = fork();

    if (child1 == 0) {
        /* First child: Prime factors */
        printf("\nChild 1 (Prime Factors): ");
        for (int i = 0; i < count; i++) {
            if (is_prime(factors[i])) {
                printf("%lld ", factors[i]);
            }
        }
        printf("\n");
        return 0;
    }

    pid_t child2 = fork();

    if (child2 == 0) {
        /* Second child: Even factors */
        printf("\nChild 2 (Even Factors): ");
        for (int i = 0; i < count; i++) {
            if (factors[i] % 2 == 0) {
                printf("%lld ", factors[i]);
            }
        }
        printf("\n");
        return 0;
    }

    /* Parent waits for both children */
    wait(NULL);
    wait(NULL);

    printf("\nParent: Both children finished.\n");
    return 0;
}
