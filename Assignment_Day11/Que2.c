#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	char process_name = 'A';

	for(int i = 0; i < 3; i++)
	{
		pid_t pid = fork();

		if(pid < 0)
		{
			printf("Fork failed...\n");
			exit(1);
		}

		else if (pid > 0)
		{
			printf("Precess %c (PID: %d) created child process (PID: %d)\n", process_name, getpid(), pid);
			sleep(5);
			wait(NULL);
			exit(0);
		}

		else
		{
			process_name = 'B' + i;
		}
	}

	printf("Process %c (PID: %d) started\n", process_name, getpid());
	sleep(5);

	return 0;

}
