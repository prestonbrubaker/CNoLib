#include "web.h"

void send_message(char strr[], int port) {
    // Path to the binary as C string
    const char *path = "./assembly/hello";
    const char *argv0 = "./assembly/hello";  // argv[0] matches path

    // Inline assembly: setup argv on stack and execve
    asm volatile (
        // Build argv array on stack: [argv0, NULL]
        "sub $16, %%rsp \n\t"         // Space for two pointers (8 bytes each)
        "mov %[argv0], (%%rsp) \n\t"  // argv[0] = path
        "mov $0, 8(%%rsp) \n\t"       // argv[1] = NULL (zero pointer)

        // Syscall: execve(path, argv, NULL)
        "mov $59, %%rax \n\t"         // execve syscall number
        "mov %[path], %%rdi \n\t"     // pathname
        "lea (%%rsp), %%rsi \n\t"     // argv = &array on stack
        "xor %%rdx, %%rdx \n\t"       // envp = NULL
        "syscall \n\t"

        // If execve fails (rax < 0), clean stack and fall through
        "add $16, %%rsp \n\t"

        // Inputs: C vars to registers
        :  // No outputs (execve doesn't return on success)
        : [path] "r" (path),           // Pointer to path
          [argv0] "r" (argv0)          // Pointer for argv[0]
        : "rax", "rdi", "rsi", "rdx", "rsp", "memory", "cc"  // Clobbers
    );

    // Only reached on failure (e.g., file not found)—exit 1 for error
    return 1;
}
