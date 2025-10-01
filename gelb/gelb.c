#include "../hello/hello.h"
#include "gelb.h"

void gelb(void)
{
    static char gelb_code[] = "\033[93m";
    static char poop_code[] = "p00p";
    static char reset_code[] = "\033[0m";
    static long gelb_len = 5;
    static long reset_len = 4;
    long ret;
    (void)gelb_code[0]; // Dummy use: Forces stack allocation and address computation
    (void)poop_code[0];
    (void)reset_code[0];
    // Optional barrier for extra safety (still harmless)
    asm volatile("" : : "m"(poop_code) : "memory");
    // Write gelb color code
    // asm volatile(
    //     "mov $1, %%rax\n"
    //     "mov $1, %%rdi\n"
    //     "mov %1, %%rsi\n"
    //     "mov $6, %%rdx\n"
    //     "syscall\n"
    //     : "=a"(ret)
    //     : "r"(gelb_code), "r"(gelb_len)
    //     : "rcx", "rdi", "rsi", "rdx", "r11", "memory");

    // asm volatile(
    //     "mov $1, %%rax\n"                             // Syscall: write (1)
    //     "mov $1, %%rdi\n"                             // fd=1 (stdout)
    //     "mov %1, %%rsi\n"                             // Buffer address
    //     "mov %2, %%rdx\n"                             // Length (from str_len)
    //     "syscall\n"                                   // Invoke
    //     : "=a"(ret)                                   // Output: rax -> ret
    //     : "r"(gelb_code), "r"(gelb_len)               // %1 = strr addr, %2 = str_len
    //     : "rcx", "rdi", "rsi", "rdx", "r11", "memory" // Full clobbers
    // );

for (int i=0;i<15;i++) {
    if (i < 6) {
        printChar(gelb_code[i]);
    }else if (i >= 6 && i < 11) {
        printChar(poop_code[i - 6]);
    }else if (i >= 11) {
        printChar(reset_code[i - 11]);
    }
}
    // asm volatile(
    //     "mov $1, %%rax\n"                             // Syscall: write (1)
    //     "mov $1, %%rdi\n"                             // fd=1 (stdout)
    //     "mov %1, %%rsi\n"                             // Buffer address
    //     "mov %2, %%rdx\n"                             // Length (from str_len)
    //     "syscall\n"                                   // Invoke
    //     : "=a"(ret)                                   // Output: rax -> ret
    //     : "r"(reset_code), "r"(gelb_len)               // %1 = strr addr, %2 = str_len
    //     : "rcx", "rdi", "rsi", "rdx", "r11", "memory" // Full clobbers
    // );
    // Write reset color code
//     asm volatile(
//         "mov $1, %%rax\n"
//         "mov $1, %%rdi\n"
//         "mov %1, %%rsi\n"
//         "mov $5, %%rdx\n"
//         "syscall\n"
//         : "=a"(ret)
//         : "r"(reset_code), "r"(reset_len)
//         : "rcx", "rdi", "rsi", "rdx", "r11", "memory");
// }

}