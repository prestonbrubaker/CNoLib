#include "../hello/hello.h"
#include "gelb.h"

void gelb(void)
{
    char gelb_code[] = "\033[93m";
    static char reset_code[] = "\033[0m";
    static long gelb_len = 5;
    static long reset_len = 4;
    long ret;

    // Write gelb color code

    asm volatile(
        "mov $1, %%rax;" // System call number for write (1)
        "mov $1, %%rdi;" // File descriptor 1 (stdout)
        "mov %0, %%rsi;" // Address of the message
        "mov %1, %%rdx;" // Length of the message
        "syscall;"       // Invoke the system call
        :
        : "r"(gelb_code), "r"((long)gelb_len)
        : "%rax", "%rdi", "%rsi", "%rdx");

    hello();

    // Write reset color code

    asm volatile(
        "mov $1, %%rax;" // System call number for write (1)
        "mov $1, %%rdi;" // File descriptor 1 (stdout)
        "mov %0, %%rsi;" // Address of the message
        "mov %1, %%rdx;" // Length of the message
        "syscall;"       // Invoke the system call
        :
        : "r"(reset_code), "r"((long)reset_len)
        : "%rax", "%rdi", "%rsi", "%rdx");
}