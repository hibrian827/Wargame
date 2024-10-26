// gcc chall.c -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <assert.h>
#include <inttypes.h>

#define MAX_USERNAME_LEN 10
#define MAX_NUM_ACCOUNT 10
#define MEMO_SIZE 0x20

typedef struct Password {
    uint32_t length;
    uint32_t real_length;
    char content[0]; // dynamic size
} Password;

typedef struct Account {
    char *memo;
    Password *password;
    char username[MAX_USERNAME_LEN];
} Account;

char *Malloc(unsigned int size) {
    char *ptr = malloc(size);
    if (!ptr) {
        puts("Memory allocation failed!");
        exit(1);
    }
    return ptr;
}

char *Free(void *ptr) {
    free(ptr);
}

void welcome() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    puts("__        __   _                            _                      ");
    puts("\\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___                ");
    puts(" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\               ");
    puts("  \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |              ");
    puts(" _ \\_/\\_/ \\___|_|\\___\\___/|_|_|_| |_|\\___|  \\__\\___/               ");
    puts("| | | | ___  __ _ _ __    / _ \\__   _____ _ __ / _| | _____      __");
    puts("| |_| |/ _ \\/ _` | '_ \\  | | | \\ \\ / / _ \\ '__| |_| |/ _ \\ \\ /\\ / /");
    puts("|  _  |  __/ (_| | |_) | | |_| |\\ V /  __/ |  |  _| | (_) \\ V  V / ");
    puts("|_| |_|\\___|\\__,_| .__/   \\___/  \\_/ \\___|_|  |_| |_|\\___/ \\_/\\_/  ");
    puts("  ____ _         |_| _                       _                     ");
    puts(" / ___| |__   __ _| | | ___ _ __   __ _  ___| |                    ");
    puts("| |   | '_ \\ / _` | | |/ _ \\ '_ \\ / _` |/ _ \\ |                    ");
    puts("| |___| | | | (_| | | |  __/ | | | (_| |  __/_|                    ");
    puts(" \\____|_| |_|\\__,_|_|_|\\___|_| |_|\\__, |\\___(_)                    ");
    puts("                                  |___/                            ");
}

Account *accounts[MAX_NUM_ACCOUNT];
Account *logged_in_account = NULL;
Account *admin_account = NULL;
int accnt_idx = 0;
int logged_in = 0;

void init_admin() {
    Account *admin = (Account *)Malloc(sizeof(Account));
    
    char msg[] = "Can you guess my password?";
    strcpy(admin->username, "admin");
    admin->memo = Malloc(MEMO_SIZE);
    memset(admin->memo, 0, MEMO_SIZE);
    memcpy(admin->memo, msg, sizeof(msg));

    int password_len = 0x10;
    admin->password = (Password *)Malloc(sizeof(Password) + password_len);
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        goto err;
    }

    int real_length = read(fd, admin->password->content, password_len);
    if (real_length < 0x10) {
        goto err;
    }
    admin->password->length = password_len;
    admin->password->real_length = real_length;

    accounts[accnt_idx++] = admin_account = admin;
    return;

err:
    puts("Something went wrong. Please contact the admin.");
    exit(1);
}

Account *find_account_by_username(char *username) {
    for (int i = 0; i < accnt_idx; i++) {
        if (memcmp(accounts[i]->username, username, MAX_USERNAME_LEN) == 0) {
            return accounts[i];
        }
    }
    return NULL;
}

int readline(char *buf, int size) {
    int i = 0;
    char c;
    assert(size > 0);
    while (i < size - 1) {
        if (read(0, &c, 1) <= 0) {
            exit(1);
        }
        if (c == '\n') {
            break;
        }
        buf[i++] = c;
    }
    buf[i] = '\0';
    return i;
}

int main() {
    welcome();
    init_admin();
    
    while (1) {
        puts("\n=== Menu ===");
        puts("1. Create account");
        puts("2. Login");
        puts("3. Change password");
        puts("4. Show profile");
        puts("5. Logout");
        puts("6. Exit");
        printf("> ");
        int choice = 0;
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                puts("=== Create account ===");
                if (accnt_idx >= MAX_NUM_ACCOUNT) {
                    puts("Too many accounts!");
                    break;
                }

                puts("Enter username: ");
                char username[MAX_USERNAME_LEN] = {0, };
                int find = 0;
                readline(username, MAX_USERNAME_LEN);
                if(find_account_by_username(username)) {
                    printf("Username '%s' Exist", username);
                    break;
                }

                // Account creation
                Account *accnt = (Account *)Malloc(sizeof(Account));
                puts("Enter username: ");
                memcpy(accnt->username, username, MAX_USERNAME_LEN);

                // Password creation
                uint64_t password_len;
                puts("How long is your password?");
                scanf("%lu", &password_len);
                getchar();
                accnt->password = (Password *)Malloc(sizeof(Password) + password_len);
                puts("Enter password: ");
                uint64_t real_length = read(0, accnt->password->content, password_len);
                accnt->password->length = password_len;
                accnt->password->real_length = real_length;

                // Memo creation
                accnt->memo = Malloc(MEMO_SIZE);
                puts("Enter memo: ");
                memset(accnt->memo, 0, MEMO_SIZE);
                read(0, accnt->memo, MEMO_SIZE);

                accounts[accnt_idx++] = accnt;
                printf("'%s' account created!\n", accnt->username);
                break;
            }
            case 2: {
                puts("=== Login ===");
                if (logged_in_account) {
                    printf("You are already logged in as %s!", logged_in_account->username);
                    break;
                }

                puts("Enter username: ");
                char username[MAX_USERNAME_LEN] = {0, };
                int find = 0;
                readline(username, MAX_USERNAME_LEN);
                Account *accnt = find_account_by_username(username);
                if (!accnt) {
                    printf("Username '%s' not found!", username);
                    break;
                }

                puts("Enter password: ");
                char in, failed = 0;
                uint32_t passwd_idx = 0;

                while (passwd_idx < accnt->password->real_length) {
                    read(0, &in, 1);
                    if (in != accnt->password->content[passwd_idx]) {
                        failed = 1;
                    }
                    passwd_idx++;
                }

                if (failed) {
                    puts("Login failed!");
                    break;
                }
                
                printf("Welcome, %s!", accnt->username);
                logged_in_account = accnt;
                break;
            }
            case 3: {
                puts("=== Change password ===");
                if (!logged_in_account) {
                    puts("You need to login first!");
                    break;
                }
                puts("Enter new password: ");
                Password *mypass = logged_in_account->password;
                mypass->real_length = read(0, mypass->content, mypass->length);
                puts("Password changed!");
                break;
            }
            case 4: {
                puts("=== Show profile ===");
                if (!logged_in_account) {
                    puts("You need to login first!");
                    break;
                }
                printf("Username: %s\n", logged_in_account->username);
                printf("Memo: ");
                write(1, logged_in_account->memo, MEMO_SIZE);
                break;
            }
            case 5: {
                puts("=== Logout ===");
                if (!logged_in_account) {
                    puts("You are not logged in!");
                    break;
                }
                logged_in_account = NULL;
                puts("Logged out!");
                break;
            }
            case 6:
                puts("Bye!");
                return 0;
            case -1: {
                puts("=== Under development ===");
                if (logged_in_account == admin_account) {
                    puts("Welcome, admin!");
                    system("/bin/sh");
                }
                break;
            }
            default:
                puts("Invalid choice!");
                break;
        }
    }
}
