#include "add/add.h"
#include "hello/hello.h"
#include "time/time.h"

int main() {

    struct timeval tv;  // The struct to fill with epoch time
    
    get_time(&tv);

    unsigned char buffer[16];  //8 * 2 = 16 bytes
    for (int i=0;i<16;i++) {
        for (int j=7;j>=0;j--) {
            if ((buffer[i] >> j) &1) {
                print0();
            } else {
                print1();
            }
        }
        printNL();
    }
    printNL();

    static char strr[] = "h";       // String to write
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



    return 0;  // Success
}