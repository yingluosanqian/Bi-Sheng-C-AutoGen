/*
7_owned-struct-类型.md
15. Implement destructor for owned struct 'Socket' that closes connection
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int fd;
} Socket;

void socket_close(Socket *sock) {
    if (sock->fd != -1) {
        close(sock->fd);
        sock->fd = -1;
    }
}

Socket socket_create(int fd) {
    Socket sock = {.fd = fd};
    return sock;
}

int main() {
    // In a real program, this would be an actual file descriptor from socket()
    int test_fd = 42; 
    
    Socket sock = socket_create(test_fd);
    
    // Simulate using the socket
    printf("Socket created with fd: %d\n", sock.fd);
    
    // Manually close the socket in C
    socket_close(&sock);
    
    return 0;
}