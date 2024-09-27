/*
    gcc -o level1 level1.c -fno-stack-protector -fcf-protection=none 
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define NAME_LEN    32

void win() {
    system("/bin/sh");
    exit(1);
}

void copy_name(char *src) {
    char name[NAME_LEN] = {0};

    strcpy(name, src);

    printf("Your name is %s\n", name);
    
    return;
}

void init() {
    // disable stream buffering
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);
}

int main(int argc) {
    char name[256] = {0};
    
    init();
    puts("=== level 1 ===");
    printf("Hint: <<< %p >>>\n", &main);

    read(0, name, 256);
    copy_name(name);

    return 0;
}
