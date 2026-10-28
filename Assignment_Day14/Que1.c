#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    
    pid_t pid = fork();
    if (pid == 0) {
        close(p1[0]);
        close(p2[1]);
        
        int nums[2] = {15, 27};
        write(p1[1], nums, sizeof(nums));
        
        int sum;
        read(p2[0], &sum, sizeof(sum));
        printf("Result from parent: %d\n", sum);
        
        close(p1[1]);
        close(p2[0]);
        return 0;
    } else {
        close(p1[1]);
        close(p2[0]);
        
        int nums[2];
        read(p1[0], nums, sizeof(nums));
        
        int sum = nums[0] + nums[1];
        write(p2[1], &sum, sizeof(sum));
        
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    return 0;
}
