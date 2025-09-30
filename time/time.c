#include "time.h"

void get_time(struct timeval *tp) {
    long ret;  // Syscall return (0 on success for gettimeofday)

    asm volatile(
        "mov $96, %%rax\n"    // Syscall #96: gettimeofday
        "mov $0, %%rsi\n"     // Arg2: NULL for timezone → rsi
        "syscall\n"           // Invoke kernel
        : "=a" (ret)          // Output: rax → ret (return code)
        : "D" (tp)           // Input: Arg1: &tv → rdi
        : "rcx", "rsi", "r11", "memory"  // Clobbers (omitted rdi)
    );
    
}
