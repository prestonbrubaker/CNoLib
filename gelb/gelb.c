#include "../hello/hello.h"
#include "gelb.h"

void gelb(void)
{
    static char gelb_code[] = "\033[93m";
    static char reset_code[] = "\033[0m";
    static long gelb_len = 5;
    static long reset_len = 4;
    long ret;

    // Write gelb color code
    asm volatile(
        "mov $1, %%rax\n"
        "mov $1, %%rdi\n"
        "mov %1, %%rsi\n"
        "mov $6, %%rdx\n"
        "syscall\n"
        : "=a"(ret)
        : "r"(gelb_code), "r"(gelb_len)
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory");

    hello();

    // Write reset color code
    asm volatile(
        "mov $1, %%rax\n"
        "mov $1, %%rdi\n"
        "mov %1, %%rsi\n"
        "mov $5, %%rdx\n"
        "syscall\n"
        : "=a"(ret)
        : "r"(reset_code), "r"(reset_len)
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory");
}