#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
	char input[100];
	char *args[10];

	signal(SIGINT, SIG_IGN);

	while(1)
	{
		printf("ignoring-shell> ");
		fflush(stdout);

		if(!fgets(input, sizeof(input), stdin))
			break;
		input[strcspn(input, "\n")] == '\0';

		int i = 0;
		args[i] = strtok(input, " ");
		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}

		if(args[0] == NULL)
			continue;
		if(strcmp(args[0], "exit") == 0)
			break;

		pid_t pid = fork();

		if(pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			execvp(args[0], args);
			perror("Cammand failed\n");
			exit(1);
		}

		else
		{
			waitpid(pid, NULL, 0);
		}
	}

	return 0;
}
