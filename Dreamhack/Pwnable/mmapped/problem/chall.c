// Name: chall.c
// Compile: gcc -fno-stack-protector chall.c -o chall

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FLAG_SIZE 0x45

void initialize() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

int main(int argc, char *argv[]) {
    int len;
    char * fake_flag_addr;
    char buf[0x20];
    int fd;
    char * real_flag_addr;

    initialize();

    fd = open("./flag", O_RDONLY);
    len = FLAG_SIZE;
    fake_flag_addr = "DH{****************************************************************}";

    printf("fake flag address: %p\n", fake_flag_addr);
    printf("buf address: %p\n", buf);

    real_flag_addr = (char *)mmap(NULL, FLAG_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
    printf("real flag address (mmapped address): %p\n", real_flag_addr);

    printf("%s", "input: ");
    read(0, buf, 60);

    mprotect(real_flag_addr, len, PROT_NONE);

    write(1, fake_flag_addr, FLAG_SIZE);
    printf("\nbuf value: ");
    puts(buf);

    munmap(real_flag_addr, FLAG_SIZE);
    close(fd);

    return 0;
}
