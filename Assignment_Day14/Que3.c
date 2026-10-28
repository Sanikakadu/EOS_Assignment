#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[2];
    pipe(arr);
    
    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(arr[0]);
        dup2(arr[1], 1);
        close(arr[1]);
        execlp("who", "who", NULL);
        return 1;
    }
    
    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(arr[1]);
        dup2(arr[0], 0);
        close(arr[0]);
        execlp("wc", "wc", NULL);
        return 1;
    }
    
    close(arr[1]);
    close(arr[0]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return 0;
}

