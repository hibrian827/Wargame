// Name: chall.c
// Compile: gcc -Wall -no-pie chall.c -o chall ; strip chall
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct person_t {
    char nationality[32];
    char name[56];
    double height;
    int age;
    char male_or_female[4];
};

void get_shell() {
    execve("/bin/sh", 0, 0);
}

void read_input(char *ptr, size_t len) {
    ssize_t readn;

    readn = read(0, ptr, len);
    if (readn < 1) {
        puts("read() error");
        exit(1);
    }

    if (ptr[readn - 1] == '\n') {
        ptr[readn - 1] = '\0';
    }
}

int main() {
    struct person_t person;

    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    printf("Enter name: ");
    read_input(person.name, 56);

    printf("Enter age: ");
    scanf("%d", &person.age);

    printf("Enter height: ");
    scanf("%lf", &person.height);

    printf("Enter M (Male) or F (Female): ");
    read_input(person.male_or_female, 5);

    printf("Hi %s.\n", person.name);

    printf("What's your nationality? ");
    read_input(person.nationality, 128);

    return 0;
}