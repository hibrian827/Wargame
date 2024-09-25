#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void initialize() {
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stdin, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IOLBF, 0);
}

int verify(uint8_t *sh, int len) {
    const uint8_t banned[] = {
        0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8E, // MOV
        0xA0, 0xA1, 0xA2, 0xA3, // MOV
        0xA4, 0xA5, // MOVS
        0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, // MOV
        0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, // MOV
        0xC6, 0xC7 // MOV
    };

    for (int i = 0; i < len; i++)
        for (int j = 0; j < sizeof(banned); j++)
            if (sh[i] == banned[j])
                return 0;
    
    return 1;
}

uint8_t *get_mmaped_page() {
    int urandom_fd = open("/dev/urandom", O_RDONLY);
    uint64_t addr;
    if (read(urandom_fd, &addr, sizeof(uint64_t)) != sizeof(uint64_t)) {
        puts("Failed to read /dev/urandom");
        return 0;
    }
    addr &= 0xffffffff000ul;

    close(urandom_fd);
    
    uint8_t *page = mmap((void *)addr, 0x1000, 7, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    if (page == MAP_FAILED || page != (uint8_t *) addr) {
        puts("Failed to mmap");
        return 0;
    }

    return page;
}

int main() {
    initialize();

    uint8_t *sh = get_mmaped_page();
    uint8_t *stack = get_mmaped_page();
    if (!sh || !stack) {
        puts("Failed mmap");
        return 1;
    }
    memset(sh, 0x90, 0x1000);
    memset(stack, 0, 0x1000);

    printf("Give me your shellcode > ");
    int len = read(0, sh, 0x800);

    if (verify(sh, len)) {
        // Setup return address
        *((uint64_t *)(stack + 0x7f8)) = (uint64_t)sh;

        // Initialize registers...
        asm("xor %rbx, %rbx");
        asm("xor %rcx, %rcx");
        asm("xor %rdx, %rdx");
        asm("xor %rdi, %rdi");
        asm("xor %rsi, %rsi");
        asm("xor %r8, %r8");
        asm("xor %r9, %r9");
        asm("xor %r10, %r10");
        asm("xor %r11, %r11");
        asm("xor %r12, %r12");
        asm("xor %r13, %r13");
        asm("xor %r14, %r14");
        asm("xor %r15, %r15");

        // Setup new stack frame
        asm("mov %0, %%rsp" :: "r"(stack + 0x7f8));
        asm("mov %0, %%rbp" :: "r"(stack + 0x800));
        asm("xor %rax, %rax");

        // Jump to shellcode
        asm("ret");
    } else {
        puts("No.");
    }
    return 0;
}