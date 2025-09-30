#include "hello.h"

void hello(void) {
    static char strr[] = "hello\n";       // String to write
    static long str_len = 7;              // Length of strr
    long ret;

    asm volatile (
        "mov $1, %%rax\n"      // Syscall: write (1)
        "mov $1, %%rdi\n"      // fd=1 (stdout)
        "mov %1, %%rsi\n"      // Buffer (strr address)
        "mov $7, %%rdx\n"      // Length=6
        "syscall\n"            // Invoke
        : "=a" (ret)           // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // Inputs: strr=%1, str_len=%2
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"
    );
}

void print0(void) {
    static char strr[] = "0";       // String to write
    static long str_len = 1;              // Length of strr
    long ret;

    asm volatile (
        "mov $1, %%rax\n"      // Syscall: write (1)
        "mov $1, %%rdi\n"      // fd=1 (stdout)
        "mov %1, %%rsi\n"      // Buffer (strr address)
        "mov $1, %%rdx\n"      // Length=6
        "syscall\n"            // Invoke
        : "=a" (ret)           // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // Inputs: strr=%1, str_len=%2
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"
    );
}

void print1(void) {
    static char strr[] = "1";       // String to write
    static long str_len = 1;              // Length of strr
    long ret;

    asm volatile (
        "mov $1, %%rax\n"      // Syscall: write (1)
        "mov $1, %%rdi\n"      // fd=1 (stdout)
        "mov %1, %%rsi\n"      // Buffer (strr address)
        "mov $1, %%rdx\n"      // Length=6
        "syscall\n"            // Invoke
        : "=a" (ret)           // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // Inputs: strr=%1, str_len=%2
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"
    );
}

void printNL(void) {
    static char strr[] = "\n";       // String to write
    static long str_len = 1;              // Length of strr
    long ret;

    asm volatile (
        "mov $1, %%rax\n"      // Syscall: write (1)
        "mov $1, %%rdi\n"      // fd=1 (stdout)
        "mov %1, %%rsi\n"      // Buffer (strr address)
        "mov $1, %%rdx\n"      // Length=6
        "syscall\n"            // Invoke
        : "=a" (ret)           // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // Inputs: strr=%1, str_len=%2
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"
    );
}