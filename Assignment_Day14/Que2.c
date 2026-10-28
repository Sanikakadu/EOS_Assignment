#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int p[2];
    pipe(p);
    
    int flags = fcntl(p[1], F_GETFL);
    fcntl(p[1], F_SETFL, flags | O_NONBLOCK);
    
    char buffer = 'A';
    int total_bytes = 0;
    
    while (write(p[1], &buffer, 1) > 0) {
        total_bytes++;
    }
    
    printf("Pipe buffer size: %d bytes\n", total_bytes);
    
    close(p[0]);
    close(p[1]);
    return 0;
}

