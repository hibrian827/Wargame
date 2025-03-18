// Name: find_candy.c
// Compile Option: gcc -Wall find_candy.c -o find_candy -lseccomp

#include <asm/prctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <seccomp.h>

#define HandleError(s) {puts(s); exit(1);}

void Init() {
    int fd;
    unsigned int seed;

    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stdin, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IOLBF, 0);

    if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
        HandleError("open error");

    if ((read(fd, &seed, 4)) == -1)
        HandleError("read error");

    srand(seed);

    seed = 0;
}

void Sandbox() {
    scmp_filter_ctx ctx;

    if ((ctx = seccomp_init(SCMP_ACT_KILL)) == NULL)
        HandleError("seccomp error");

    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl), 0);

    if (seccomp_load(ctx) < 0) {
      seccomp_release(ctx);
      HandleError("seccomp error");
    }
    seccomp_release(ctx);

    arch_prctl(ARCH_SET_FS, NULL);
    arch_prctl(ARCH_SET_GS, NULL);
}

// Initialize registers with null.
uint8_t stub[] = "H1\xc0H1\xdbH1\xc9H1\xd2H1\xf6H1\xffH1\xedM1\xc0M1"
                 "\xc9M1\xd2M1\xdbM1\xe4M1\xedM1\xf6M1\xff\xc5\xfc\x77";

int main() {
    int fd;
    uint8_t *sh;
    void *flag_mem;
    void *stack_mem;

    puts("___      .-\"\"-.      ___\n" \
         "\\  \"-.  / \\ \\ \\\\  .-\"  /\n" \
         " > -=.\\/ \\ \\ \\ \\\\/.=- <\n" \
         " > -='/\\\\ \\ \\ \\ /\\'=- <\n" \
         "/__.-'  \\\\ \\ \\ /  '-.__\\\n" \
         "         '-..-'");
    Init();

    // Insert flag into somewhere.
    if ((fd = open("./flag", O_RDONLY)) == -1)
        HandleError("open error");

    flag_mem = mmap((void *)((((uint64_t)rand() << 12) & 0x0000fffff000) | 0x080000000000), 0x1000, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    if (flag_mem == MAP_FAILED)
        HandleError("mmap error");

    if (read(fd, flag_mem, 0x500) == -1)
        HandleError("read error");

    close(fd);

    // Create a space for shellcode and initialize it.
    sh = mmap((void *)0xbeefdead000, 0x1000, 7, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    if (sh == MAP_FAILED)
        HandleError("mmap error");

    memset(sh, 0x90, 0x1000);
    memcpy(sh, stub, sizeof(stub) - 1);

    // Create a stack space for rsp.
    stack_mem = mmap((void *)0xdeadbeef000, 0x1000, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    if (stack_mem == MAP_FAILED)
        HandleError("mmap error");

    // Get and execute shellcode.
    puts("find me :) ");
    sleep(1);
    printf("shellcode: ");
    read(0, sh + sizeof(stub) - 1, 1000);

    // sys_write and sys_arch_prctl are allowed.
    // sys_arch_prctl is used to initialize fs and gs.
    Sandbox();
    asm("mov %0, %%rsp" :: "r"(stack_mem));
    asm("add $0x800, %rsp");

    asm("mov %0, %%rax" :: "r"(sh));

    fd = 0;
    sh = 0;
    flag_mem = 0;
    stack_mem = 0;

    asm("jmp *%rax");

    return 0;
}
