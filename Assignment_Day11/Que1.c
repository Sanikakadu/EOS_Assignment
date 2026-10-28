#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	for(int i  =1; i <= 5; i++)
	{
		pid_t pid = fork();

		if(pid < 0)
		{
			perror("fork faild\n");
			exit(1);
		}

		else if(pid == 0)
		{
			printf("Child (%d) PID : %d started\n", i, getpid());
			sleep(5);

			printf("Child (%d) PID : %d finished\n", i, getpid());
			exit(0);
		}
	}
	
	printf("Parent waiting for children to complete...\n");
	while(wait(NULL) > 0);
	printf("Parent All child cleanup.Existing\n");

	return 0;
}
