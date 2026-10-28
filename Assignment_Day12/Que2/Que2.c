#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	pid_t pid1, pid2, pid3, pid4, pid5, pid6;
	int status;
	int success = 1;

	printf("parent starting concurrent compilation...\n");

	pid1 = fork();
	if(pid1 == 0)
	{
		execlp("gcc", "gcc", "-c", "circle.c", NULL);
		exit(1);
	}

	pid2 = fork();
	if(pid2 == 0)
	{
		execlp("gcc", "gcc", "-c", "square.c", NULL);
		exit(1);
	}

	pid3 = fork();
	if(pid3 == 0)
	{
		execlp("gcc", "gcc", "-c", "rectangle.c", NULL);
		exit(1);
	}

	pid4 = fork();
	if(pid4 == 0)
	{
		execlp("gcc", "gcc", "-c", "main.c", NULL);
		exit(1);
	}

	waitpid(pid1, &status, 0);
	if(WEXITSTATUS(status) != 0) 
		success = 0;

	waitpid(pid2, &status, 0);
	if(WEXITSTATUS(status) != 0) 
		success = 0;
	
	waitpid(pid3, &status, 0);
	if(WEXITSTATUS(status) != 0) 
		success = 0;

	waitpid(pid4, &status, 0);
	if(WEXITSTATUS(status) != 0) 
		success = 0;

	if(success == 0)
	{
		printf("parent error: one or more files failed to compile.\n");
		return 1;
	}

	printf("parent linking object files...\n");
	
	pid5 = fork();
	if(pid5 == 0)
	{
		execlp("gcc", "gcc", "-o", "Que1.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL);
		exit(1);
	}
	printf("Parent linking complete successfully\n");

	printf("parent executing Que1.out.\n");
	pid6 = fork();
	if(pid6 == 0)
	{
		execlp("./Que1.out", "./Que1.out", NULL);
		exit(1);
	}

	waitpid(pid6, &status, 0);
	printf("parent execution finished. Child exit status: %d\n", WEXITSTATUS(status));

	return 0;
}
