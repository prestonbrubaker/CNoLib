#include "web.h"


struct in_addr {
    unsigned int s_addr;
};

struct sockaddr_in {
    unsigned short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

void send_message(char strr[], int port) {
    
    static char msg[] = "Hello\n";
    static long msg_len = 6;
    long sockfd, client_fd;

    static struct sockaddr_in addr = {
    .sin_family = 2,        // 2
    .sin_port = ((9027 & 0xFF) << 8) | ((9027 >> 8) & 0xFF),      // Your port in network byte order
    .sin_addr.s_addr = 0, // 0 - bind to all interfaces
    .sin_zero = {0}               // Zero the 8-byte padding
    };
    // addr.sin_family = 2;
    // addr.sin_port = ((9027 & 0xFF) << 8) | ((9027 >> 8) & 0xFF);  // htons(8080)
    // addr.sin_addr.s_addr = 0;

    long ret;

    asm volatile ("" : : "m" (msg) : "memory");
    // Syscall: socket(AF_INET=2, SOCK_STREAM=1, protocol=0)
    asm volatile (
        "mov $41, %%rax\n"
        "mov $2, %%rdi\n"
        "mov $1, %%rsi\n"
        "mov $0, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (sockfd)
        :
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"
    );

    // Set socket to blocking mode
    asm volatile (
        "mov $72, %%rax\n"
        "mov $3, %%rdi\n"
        "mov $4, %%rsi\n"
        "mov $0, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (ret)
        : "r" (sockfd)
        : "rcx", "r11", "rdi", "rsi", "rdx", "memory"
    );

    int optval = 1; // Enable SO_REUSEADDR
    asm volatile (
        "mov $54, %%rax\n"    // Syscall: setsockopt (54)
        "mov $3, %%rdi\n"     // sockfd
        "mov $1, %%rsi\n"     // SOL_SOCKET (level)
        "mov $2, %%rdx\n"     // SO_REUSEADDR (option)
        "mov $1, %%r10\n"     // Address of optval
        "mov $4, %%r8\n"      // optlen (sizeof(int))
        "syscall\n"
        :
        : "r" (sockfd), "r" (&optval)
        : "rax", "rdi", "rsi", "rdx", "r10", "r8", "rcx", "r11", "memory"
    );


    asm volatile (
        "mov $49, %%rax\n"
        "mov $3, %%rdi\n"
        "mov %0, %%rsi\n"
        "mov $16, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : 
        : "r" (&addr)
        : "rcx", "r11", "rdi", "rsi", "rdx", "memory", "r11"
    );


    // Syscall: listen(sockfd, backlog=1)
    asm volatile (
        "mov $50, %%rax\n"
        "mov $3, %%rdi\n"
        "mov $1, %%rsi\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (ret)
        : "r" (sockfd)
        : "rcx", "r11", "rdi", "rsi", "r11", "rdx", "memory"
    );



    // Syscall: accept(sockfd, NULL, NULL)
    asm volatile (
        "mov $43, %%rax\n"
        "mov $3, %%rdi\n"
        "mov $0, %%rsi\n"
        "mov $0, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (client_fd)
        : "r" (sockfd)
        : "rcx", "r11", "rdi", "rsi", "rdx", "memory"
    );

    // Syscall: sendto(client_fd, msg, msg_len, flags=0, NULL, 0)
    asm volatile (
            "mov $44, %%rax\n"
            "mov $4, %%rdi\n"
            "mov %2, %%rsi\n"
            "mov %1, %%rdx\n"
            "mov $0, %%r10\n"
            "mov $0, %%r8\n"
            "mov $0, %%r9\n"
            "syscall\n"
            :
            : "r" (client_fd), "r" (msg_len), "r" (msg)
            : "rcx", "r11", "rdi", "rsi", "rdx", "r10", "r8", "r9", "memory"
    );

    // Syscall: close(client_fd)
    asm volatile (
        "mov $3, %%rax\n"
        "mov $4, %%rdi\n"
        "syscall\n"
        :
        : "r" (client_fd)
        : "rcx", "r11", "rdi"
    );

    // Syscall: close(sockfd)
    asm volatile (
        "mov $3, %%rax\n"
        "mov $3, %%rdi\n"
        "syscall\n"
        :
        : "r" (sockfd)
        : "rcx", "r11", "rdi"
    );
}
