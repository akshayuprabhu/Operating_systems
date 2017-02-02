#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int isPrime(int a) {
    int n = (a / 2) + 1;
    int i;
    if (a < 2) {
        return 0;
    }
    for (i = 2; i < n ; i++) {
        if (a%i == 0){
            return 0;
        }
    }
    return 1;
}


int main(int argc, char const *argv[]) {
    int n,i;
    int fibo[1000];
    int pfd[2];
    if (pipe(pfd) == -1) {
        printf("Error in opening of pipe\n");
        exit(1);
    }
    pid_t pid = fork();
    if (pid > 0) {
        printf("Waiting in the parent process:\n");
        wait(NULL);
        close(pfd[1]);
        read(pfd[0],fibo,sizeof(fibo));
        printf("Prime numbers in fibonacci: ");
        for (i = 0; i < 25; i++) {
            if (isPrime(fibo[i])){
                printf("%d ",fibo[i]);
            }
        }
        printf("\nParent process complete\n");
        exit(0);
    }
    else if (pid == 0) {
        n = 25;
        close(pfd[0]);
        printf("Child process:\n");
        int i;
        fibo[0] = 0;
        fibo[1] = 1;
        for (i=2; i<n;i++){
            fibo[i] = fibo[i-1] + fibo[i-2];
        }
        write(pfd[1],fibo,sizeof(fibo));
        close(pfd[1]);
        printf("Child process complete\n");
    }
    return 0;
}
