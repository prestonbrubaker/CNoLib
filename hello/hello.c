#include "hello.h"

char message[] = "hello\n";
char zero[] = "0\n";
char one[] = "1\n";
char enter[] = "\n";
const int hello_buffer = 6;
const int binary_buffer = 2;

void hello()
{
    asm volatile(
        "mov $1, %%rax;" // System call number for write (1)
        "mov $1, %%rdi;" // File descriptor 1 (stdout)
        "mov %0, %%rsi;" // Address of the message
        "mov %1, %%rdx;" // Length of the message
        "syscall;"       // Invoke the system call
        :
        : "r"(message), "r"((long)hello_buffer)
        : "%rax", "%rdi", "%rsi", "%rdx");
}

void print0() {
    asm volatile(
        "mov $1, %%rax;" // System call number for write (1)
        "mov $1, %%rdi;" // File descriptor 1 (stdout)
        "mov %0, %%rsi;" // Address of the message
        "mov %1, %%rdx;" // Length of the message
        "syscall;"       // Invoke the system call
        :
        : "r"(&zero), "r"((long)binary_buffer)
        : "%rax", "%rdi", "%rsi", "%rdx");
}

void print1()
{
    asm volatile(
        "mov $1, %%rax;" // System call number for write (1)
        "mov $1, %%rdi;" // File descriptor 1 (stdout)
        "mov %0, %%rsi;" // Address of the message
        "mov %1, %%rdx;" // Length of the message
        "syscall;"       // Invoke the system call
        :
        : "r"(&one), "r"((long)binary_buffer)
        : "%rax", "%rdi", "%rsi", "%rdx");
}

void newline() {
    asm volatile(
        "mov $1, %%rax;" // System call number for write (1)
        "mov $1, %%rdi;" // File descriptor 1 (stdout)
        "mov %0, %%rsi;" // Address of the message
        "mov %1, %%rdx;" // Length of the message
        "syscall;"       // Invoke the system call
        :
        : "r"(&enter), "r"((long)binary_buffer)
        : "%rax", "%rdi", "%rsi", "%rdx");
}

void printChar(char strrr)
{
    static char strr[2] = {0, 0};
    strr[0] = strrr;
    static const long str_len = 1;

    asm volatile(
        "mov $1, %%rax;" // System call number for write (1)
        "mov $1, %%rdi;" // File descriptor 1 (stdout)
        "mov %0, %%rsi;" // Address of the message
        "mov %1, %%rdx;" // Length of the message
        "syscall;"       // Invoke the system call
        :
        : "r"(strr), "r"(str_len)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11"); 
}