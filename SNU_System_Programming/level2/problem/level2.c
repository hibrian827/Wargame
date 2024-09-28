/*
    gcc -o level2 level2.c -fcf-protection=none
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define NAME_LEN    32
#define COMMENT_LEN 32

void win() {
    system("/bin/sh");
    exit(1);
}

void leave_comment() {
    char comment[COMMENT_LEN] = {0};
    printf("Leave a comment: ");
    read(0, comment, 100);
    puts("Thank you!");
    return;
}

void read_name() {
    char name[NAME_LEN] = {0}; 

    read(0, name, 256);
    printf("Your first name is %s\n", name);

    read(0, name, 256);
    printf("Your last name is %s\n", name);

    leave_comment();

    return;
}

void init() {
    // disable stream buffering
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);
}

int main(int argc) {
    init();
    puts("=== level 2 ===");
    read_name();

    return 0;
}
