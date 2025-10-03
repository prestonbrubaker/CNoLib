#include "hello.h"

void hello(void) {
    char strr[] = "hello\n";       // String to write
    (void)strr[0];      // Dummy use: Forces stack allocation and address computation

    // Optional barrier for extra safety (still harmless)
    asm volatile ("" : : "m" (strr) : "memory");
    static long str_len = 6;              // Length of strr
    long ret;

    asm volatile (
        "mov $1, %%rax\n"      // Syscall: write (1)
        "mov $1, %%rdi\n"      // fd=1 (stdout)
        "mov %1, %%rsi\n"      // Buffer (strr address)
        "mov %2, %%rdx\n"      // Length=6
        "syscall\n"            // Invoke
        : "=a" (ret)           // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // Inputs: strr=%1, str_len=%2
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"
    );
    strr[0] = '\0';
    asm volatile (
        "mov $1, %%rax\n"     // Syscall: write (1)
        "mov $1, %%rdi\n"     // fd=1 (stdout)
        "mov %1, %%rsi\n"     // Buffer address
        "mov $1, %%rdx\n"     // Length (from str_len)
        "syscall\n"           // Invoke
        : "=a" (ret)          // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // %1 = strr addr, %2 = str_len
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"  // Full clobbers
    );
}

void print0(void) {
    static char strr[] = "0";       // String to write
    (void)strr[0];      // Dummy use: Forces stack allocation and address computation

    // Optional barrier for extra safety (still harmless)
    asm volatile ("" : : "m" (strr) : "memory");
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
        strr[0] = '\0';
    asm volatile (
        "mov $1, %%rax\n"     // Syscall: write (1)
        "mov $1, %%rdi\n"     // fd=1 (stdout)
        "mov %1, %%rsi\n"     // Buffer address
        "mov $1, %%rdx\n"     // Length (from str_len)
        "syscall\n"           // Invoke
        : "=a" (ret)          // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // %1 = strr addr, %2 = str_len
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"  // Full clobbers
    );
}

void print1(void) {
    static char strr[] = "1";       // String to write
    (void)strr[0];      // Dummy use: Forces stack allocation and address computation

    // Optional barrier for extra safety (still harmless)
    asm volatile ("" : : "m" (strr) : "memory");
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
        strr[0] = '\0';
    asm volatile (
        "mov $1, %%rax\n"     // Syscall: write (1)
        "mov $1, %%rdi\n"     // fd=1 (stdout)
        "mov %1, %%rsi\n"     // Buffer address
        "mov $1, %%rdx\n"     // Length (from str_len)
        "syscall\n"           // Invoke
        : "=a" (ret)          // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // %1 = strr addr, %2 = str_len
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"  // Full clobbers
    );
}

void printNL(void) {
    static char strr[] = "\n";       // String to write
    (void)strr[0];      // Dummy use: Forces stack allocation and address computation

    // Optional barrier for extra safety (still harmless)
    asm volatile ("" : : "m" (strr) : "memory");
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
    strr[0] = '\0';
    asm volatile (
        "mov $1, %%rax\n"     // Syscall: write (1)
        "mov $1, %%rdi\n"     // fd=1 (stdout)
        "mov %1, %%rsi\n"     // Buffer address
        "mov $1, %%rdx\n"     // Length (from str_len)
        "syscall\n"           // Invoke
        : "=a" (ret)          // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // %1 = strr addr, %2 = str_len
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"  // Full clobbers
    );
}


void printChar(char strrr) {
    char strr[] = "";
    strr[0] = strrr;
    (void)strr[0];      // Dummy use: Forces stack allocation and address computation

    // Optional barrier for extra safety (still harmless)
    asm volatile ("" : : "m" (strr) : "memory");

    static long str_len = 2;  // Your static length

    long ret;
    asm volatile (
        "mov $1, %%rax\n"     // Syscall: write (1)
        "mov $1, %%rdi\n"     // fd=1 (stdout)
        "mov %1, %%rsi\n"     // Buffer address
        "mov %2, %%rdx\n"     // Length (from str_len)
        "syscall\n"           // Invoke
        : "=a" (ret)          // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // %1 = strr addr, %2 = str_len
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"  // Full clobbers
    );
    strr[0] = '\0';
    asm volatile (
        "mov $1, %%rax\n"     // Syscall: write (1)
        "mov $1, %%rdi\n"     // fd=1 (stdout)
        "mov %1, %%rsi\n"     // Buffer address
        "mov %2, %%rdx\n"     // Length (from str_len)
        "syscall\n"           // Invoke
        : "=a" (ret)          // Output: rax -> ret
        : "r" (strr), "r" (str_len)  // %1 = strr addr, %2 = str_len
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"  // Full clobbers
    );
}