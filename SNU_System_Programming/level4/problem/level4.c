/*
    gcc level4.c -o level4
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

#define _MAX_USERNAME_LENGTH 15
#define MAX_USERNAME_LENGTH (_MAX_USERNAME_LENGTH + 1)
#define FORMAT_USERNAME "%" TO_STRING(_MAX_USERNAME_LENGTH) "s"

#define _MAX_PASSWORD_LENGTH 31
#define MAX_PASSWORD_LENGTH (_MAX_PASSWORD_LENGTH + 1)
#define FORMAT_PASSWORD "%" TO_STRING(_MAX_PASSWORD_LENGTH) "s"

#define MAX_ACCOUNTS 10
#define USERNAME_ADMIN "admin"

typedef struct Username {
    char username[MAX_USERNAME_LENGTH];
} Username;

typedef struct Password {
    char password[MAX_PASSWORD_LENGTH];
} Password;

typedef struct Account {
    Username *u;
    Password *p;
} Account;

Account *admin = NULL;
Account *current_user = NULL;
Account *users[MAX_ACCOUNTS];
int user_idx = 1;

void hexdump(char *buf, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x ", buf[i]);
        if (i % 16 == 15) {
            puts("");
        }
    }
    puts("");
}

void init() {
    // disable stream buffering
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);
}

void init_admin() {
    char random[MAX_PASSWORD_LENGTH];
    int fd_random = open("/dev/urandom", O_RDONLY);
    if (read(fd_random, random, MAX_PASSWORD_LENGTH) != MAX_PASSWORD_LENGTH) {
        puts("Error reading random");
        exit(1);
    }
    close(fd_random);

    admin = (Account*)malloc(sizeof(Account));
    Password* password = (Password*)malloc(sizeof(Password));
    Username* username = (Username*)malloc(sizeof(Username));
    admin->p = password;
    admin->u = username;
    sprintf(admin->u->username, USERNAME_ADMIN);
    memcpy(admin->p->password, random, MAX_PASSWORD_LENGTH);

    users[0] = admin;
}

void prompt() {
    puts("1. Register");
    puts("2. Login");
    puts("3. Logout");
    puts("4. Shell");
    printf("> ");
}

void add_account() {
    if (user_idx >= MAX_ACCOUNTS) {
        puts("Too many users");
        return;
    }

    Account* user = (Account*)malloc(sizeof(Account));
    Password* password = (Password*)malloc(sizeof(Password));
    Username* username = (Username*)malloc(sizeof(Username));
    user->p = password;
    user->u = username;
    printf("What is your username? ");
    scanf(FORMAT_USERNAME, user->u->username);

    if (strcmp(user->u->username, USERNAME_ADMIN) == 0) {
        puts("");
        puts("[-] You cannot use this username");
        goto need_free;
    }

    printf("What is your password? ");
    scanf("%s" /* TODO: use FORMAT_PASSWORD*/, user->p->password);
    users[user_idx++] = user;
    printf("[+] Username %s registered\n", user->u->username);
    return;

need_free:
    free(user->u);
    free(user->p);
    free(user);
    return;
}

void login() {
    if (current_user != NULL) {
        puts("[-] You are already logged in");
        return;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char tmp[100];
    
    printf("Username: ");
    scanf(FORMAT_USERNAME, username);
    printf("Password: ");
    scanf("%s" /* TODO: use FORMAT_PASSWORD*/, password);

    for (int i = 0; i < user_idx; i++) {
        if (strcmp(username, users[i]->u->username) == 0 && strcmp(password, users[i]->p->password) == 0) {
            printf("Welcome %s\n", username);
            current_user = users[i];
            return;
        }
    }

    puts("Invalid username or password");
}

void logout() {
    if (current_user == NULL) {
        puts("[-] You are not logged in");
        return;
    }
    printf("[*] Goodbye %s\n", current_user->u->username);
    current_user = NULL;
}

int main() {
    puts("=== Heap Challenge! ===");

    init();
    init_admin();
    while (1) {
        int menu;
        prompt();
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                puts("[!] Register");
                add_account();
                break;
            case 2:
                puts("[!] Login");
                login();
                break;
            case 3:
                puts("[!] Logout");
                logout();
                break;
            case 4:
                puts("[!] Shell");
                if (current_user && strcmp(current_user->u->username, USERNAME_ADMIN) == 0) {
                    puts("Welcome admin");
                    system("/bin/sh");
                } else {
                    puts("[-] Oh, you are not admin");
                }
                exit(1);
                break;
            default:
                puts("Invalid choice");
                break;
        }
    }    
}
