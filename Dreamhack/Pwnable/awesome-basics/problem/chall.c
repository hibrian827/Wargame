// Name: chall.c
// Compile: gcc -zexecstack -fno-stack-protector chall.c -o chall

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define FLAG_SIZE 0x45

void alarm_handler() {
    puts("TIME OUT");
    exit(-1);
}

void initialize() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    signal(SIGALRM, alarm_handler);
    alarm(30);
}

char *flag;

int main(int argc, char *argv[]) {
    int stdin_fd = 0;
    int stdout_fd = 1;
    int flag_fd;
    int tmp_fd;
    char buf[80];

    initialize();

    // read flag
    flag = (char *)malloc(FLAG_SIZE);
    flag_fd = open("./flag", O_RDONLY);
    read(flag_fd, flag, FLAG_SIZE);
    close(flag_fd);

    tmp_fd = open("./tmp/flag", O_WRONLY);

    write(stdout_fd, "Your Input: ", 12);
    read(stdin_fd, buf, 0x80);

    write(tmp_fd, flag, FLAG_SIZE);
    write(tmp_fd, buf, 80);
    close(tmp_fd);

    return 0;
}
