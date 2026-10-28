#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define TO_PARENT 1
#define TO_CHILD  2


struct msg_buffer 
{
    long msg_type;       
    int num1;            
    int num2;            
};

int main() 
{
    
    key_t key = ftok("msgqueue_example", 65);
    if (key == -1) 
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    int msg_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_id == -1) 
    {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    { 
    	struct msg_buffer child_msg;

        child_msg.msg_type = TO_PARENT;
        child_msg.num1 = 15;
        child_msg.num2 = 27;

        printf("[Child] Sending numbers %d and %d to Parent...\n", child_msg.num1, child_msg.num2);
        msgsnd(msg_id, &child_msg, sizeof(child_msg) - sizeof(long), 0);

        msgrcv(msg_id, &child_msg, sizeof(child_msg) - sizeof(long), TO_CHILD, 0);
        printf("[Child] Received sum from Parent: %d\n", child_msg.num2);

        printf("[Child] Exiting.\n");
        exit(EXIT_SUCCESS);
    } 
    else 
    {
    	struct msg_buffer parent_msg;

	msgrcv(msg_id, &parent_msg, sizeof(parent_msg) - sizeof(long), TO_PARENT, 0);
        printf("[Parent] Received %d and %d from Child.\n", parent_msg.num1, parent_msg.num2);

         int sum = parent_msg.num1 + parent_msg.num2;
        printf("[Parent] Calculated sum: %d. Sending back to Child...\n", sum);

        parent_msg.msg_type = TO_CHILD;
        parent_msg.num2 = sum; 
        msgsnd(msg_id, &parent_msg, sizeof(parent_msg) - sizeof(long), 0);

         wait(NULL);
        printf("[Parent] Child finished. Cleaning up queue and exiting.\n");

        msgctl(msg_id, IPC_RMID, NULL);
    }

    return 0;
}

