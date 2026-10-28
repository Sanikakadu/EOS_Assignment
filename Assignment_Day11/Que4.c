#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("fork failed\n");
		exit(1);
	}

	else if(pid == 0)
	{
		printf("Child opening browser...\n");

		execlp("google-chrome", "google-chrome", "https://google.com", NULL);

		perror("could not find");
		exit(1);
	}

	else
	{
		wait(NULL);
		printf("PArent browser execution handled\n");
	}
	
	return 0;
}
