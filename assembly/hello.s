.section .data
    # sockaddr_in structure for binding (16 bytes)
    addr:
        .word 2              # sin_family = AF_INET
        .word 0x4723         # sin_port = htons(9043)
        .long 0              # sin_addr = INADDR_ANY (0.0.0.0)
        .zero 8              # sin_zero (padding)

    # HTTP response header (64 bytes)
    header:
        .ascii "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 59\r\n\r\n"
    header_len = . - header

    # Simple HTML body (59 bytes)
    body:
        .ascii "<html><body><h1>WILLOH ALERT</h1></body></html>"
    body_len = . - body
.section .text
.globl _start

_start:
    # Create socket (AF_INET, SOCK_STREAM, 0)
    mov $41, %rax         # socket syscall
    mov $2, %rdi          # domain: AF_INET
    mov $1, %rsi          # type: SOCK_STREAM
    mov $0, %rdx          # protocol: 0 (default)
    syscall
    test %rax, %rax       # Check for error (basic; ignore for now)
    js .exit              # Jump if negative

    mov %rax, %r15        # Save socket FD in %r15 (non-volatile reg)

    # Bind socket to address
    mov $49, %rax         # bind syscall
    mov %r15, %rdi        # sockfd
    lea addr(%rip), %rsi  # &addr
    mov $16, %rdx         # addrlen
    syscall
    test %rax, %rax
    js .exit

    # Listen on socket (backlog 5)
    mov $50, %rax         # listen syscall
    mov %r15, %rdi        # sockfd
    mov $5, %rsi          # backlog
    syscall
    test %rax, %rax
    js .exit

.loop:
    # Accept connection
    mov $43, %rax         # accept syscall
    mov %r15, %rdi        # sockfd
    xor %rsi, %rsi        # addr (NULL)
    xor %rdx, %rdx        # addrlen (NULL)
    syscall
    test %rax, %rax
    js .loop              # Retry on error

    mov %rax, %r14        # Save client FD in %r14

    # Write HTTP header to client
    mov $1, %rax          # write syscall
    mov %r14, %rdi        # client FD
    lea header(%rip), %rsi # buffer
    mov $header_len, %rdx # count
    syscall

    # Write HTML body to client
    mov $1, %rax          # write
    mov %r14, %rdi        # client FD
    lea body(%rip), %rsi  # buffer
    mov $body_len, %rdx   # count
    syscall

    # Close client socket
    mov $3, %rax          # close syscall
    mov %r14, %rdi        # client FD
    syscall

    jmp .loop             # Loop for next connection

.exit:
    mov $60, %rax         # exit syscall
    xor %rdi, %rdi        # status 0
    syscall