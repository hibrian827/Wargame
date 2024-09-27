/*
    gcc -o level0 level0.c -fno-stack-protector -no-pie -fcf-protection=none
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define NAME_LEN    32

void win() {
    FILE *file = fopen("flag.txt", "r");
    if (file == NULL) {
        printf("Cannot open flag.txt\n");
        printf("Please contact the admin.\n");
        exit(1);
    }

    char buffer[1024] = {0};
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
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
    puts("=== level 0 ===");

    scanf("%255s", name);
    copy_name(name);

    return 0;
}
