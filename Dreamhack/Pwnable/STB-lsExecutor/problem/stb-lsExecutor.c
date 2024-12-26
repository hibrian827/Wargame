// gcc -fno-stack-protector -no-pie -z relro -o ./stb ./stb.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void init(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

void command_check(char *command, int len){
    char *invalid_chars = "~!#$%^&*()+|\\[]{};:\'\"`<>?,./=\"{}\x0a";
    for(int i = 0; i < len; i++){
        for(int j = 0; j < strlen(invalid_chars); j++){
            if(command[i] == invalid_chars[j]){
                command[i] = 'x';
                break;
            }
        }
    }
}

void read_data(char *data, int len){
    int data_len = read(0, data, len);
    data[data_len - 1] = '\x00';
    command_check(data, data_len);
}

char sel[2];

int main(){
    int size;
    char command[100], data[60];

    init();

    for(int i = 0; i < 10; i++){
        printf("Enter option : ");
        read_data(data, 60);

        size = snprintf(command, 30, "ls ~%s ", data);

        printf("Enter path : ");
        read_data(&command[size], 70);

        system(command);

        printf("Again? y/n\n");
        read(0, sel, 2);
        if(sel[0] == 'n'){
            break;
        }
    }

    return 0;
}
