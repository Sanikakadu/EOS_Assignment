#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void clean_zombies(int sig) {
    (void)sig; 
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    char input[100];
    char *args[10];

    signal(SIGCHLD, clean_zombies);

    while (1) {
        printf("async-shell> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (args[0] == NULL) continue;
        if (strcmp(args[0], "exit") == 0) break;

        int is_background = 0;
        if (i > 0 && strcmp(args[i - 1], "&") == 0) {
            is_background = 1;
            args[i - 1] = NULL;
        }

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Command failed");
            exit(1);
        } else {
            if (is_background) {
                printf("[Started background process PID: %d]\n", pid);
               
            } else {
                waitpid(pid, NULL, 0); 
            }
        }
    }
    return 0;
}

