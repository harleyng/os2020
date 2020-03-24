#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Start forking...");
    int pid = fork();
    if (pid != 0) {
        printf("I am the parent, my first child is %d\n", pid);
        wait(NULL);
        pid = fork();
        if (pid != 0) {
            printf("I am still the parent, my second child is %d\n", pid);
            wait(NULL);
        } else {
            printf("I am 2nd child after fork(), launching free -h\n");
            char *args[] = {"/usr/bin/free", "-h", NULL};
            execvp(args[0], args);
            printf("Finished launching free -h\n");
        }
    } else {
        printf("I am 1st child after fork(), launching ps -ef\n");
        char *args[] = {"/bin/ps", "-ef", NULL};    
        execvp(args[0], args);
        printf("Finished launching ps -ef\n");
    }

    return 0;
}