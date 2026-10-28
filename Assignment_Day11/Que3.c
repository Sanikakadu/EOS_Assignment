#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{

	int count = 0;

	while(1)
	{
		pid_t pid = fork();

		if(pid < 0)
		{
			printf("Maximum child processes reached: %d\n", count);
			break;
		}

		else if(pid == 0)
		{
			exit (0);
		}

		else
		{
			count++;
		}
	}

	return 0;
}
