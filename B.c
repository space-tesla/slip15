Q.2) Write a C program which creates a child process to run a Linux/Unix command or any user-defined program. The parent process sets the signal handler for the death of the child signal and alarm signal. If a child process does not complete its execution in 5 seconds, then the parent process kills the child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

void childHandler(int sig) {
    printf("Child process terminated\n");
    exit(0);
}

void alarmHandler(int sig) {
    printf("Child process took too long. Killing it...\n");
    exit(0);
}

int main() {
    pid_t pid;
    struct sigaction sa;
    
    signal(SIGALRM, alarmHandler); // Set alarm signal handler
    signal(SIGCHLD, childHandler); // Set child termination signal handler

    pid = fork();

    if (pid == 0) {
        // Child process
        sleep(10);  // Simulating a command or process taking longer than expected
        printf("Child process completed\n");
        exit(0);
    } 
    else if (pid > 0) {
        // Parent process
        alarm(5);  // Set an alarm for 5 seconds
        wait(NULL); // Wait for child process to finish
    } 
    else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}

Output:
Child process took too long. Killing it...
