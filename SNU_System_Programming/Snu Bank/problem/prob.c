#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>

bool is_admin = false;
unsigned balance = 1000;

void alarm_handler(int signum) {
    if (!is_admin) {
        printf("Timeout! Non-admin users cannot stay logged in for more than 10 seconds.\n");
        exit(0);
    }
}

void open_admin_console() {
    system("/bin/bash");
    return;
}

void earn_money() {
    printf("Working... It would take around 1 second...");
    // Wait for 1 second
    for (int i = 0; i < 5; i++) {
        // 200,000 micro-secs == 200 mili-secs == 0.2 secs
        printf(" . ");
        usleep(200000);
    }
    printf("\n");
    printf("You have earned 1000 won");
    balance += 1000;
    return;
}

void request_system_reset() {
    if (is_admin == false) {
        // Temporarily grant admin privileges
        is_admin = true;
        printf("Resetting system ");
        for (int i = 0; i < 10; i++) {
            printf(" . ");
            usleep(300000); // 300,000 micro-secs == 300 mili-secs == 0.3 secs
        }
        printf("\n");
        balance = 0;
        is_admin = false;
    } else {
        balance = 0;
    }
}

void user_command(int command) {
    switch(command) {
        case 1:
            printf("Your current balance is: %u won\n", balance);
            break;
        case 2:
            {
                unsigned withdraw;
                printf("Enter amount to withdraw: ");
                scanf("%u", &withdraw);
                if (withdraw <= balance) {
                    balance -= withdraw;
                    printf("Withdrawn %u won. New balance: %u won.\n", withdraw, balance);
                } else {
                    printf("Insufficient funds.\n");
                }
            }
            break;
        case 3:
            earn_money();
            break;
        case 4:
            request_system_reset();
            break;
        case 5:
            if (is_admin) {
                open_admin_console();
            } else {
                printf("You are not an admin");
            }
            break;
        case 6:
            if (balance >= 20000) {
                is_admin = true;
                printf("You have been upgraded to admin.\n");
            } else {
                printf("Insufficient funds to upgrade to admin.\n");
            }
            break;
        default:
            printf("Invalid command.\n");
            break;
    }
}

int main() {
    // Set up the alarm signal handler
    signal(SIGALRM, alarm_handler);
    alarm(10);

    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);

    printf("Welcome to the SNU Bank System!\n");
    printf("You can view your balance, make a withdrawal, or attempt to purchase the flag.\n");

    while (1) {
        printf("\nCommands:\n");
        printf("1. View Balance\n");
        printf("2. Withdraw Money\n");
        printf("3. Earn Money\n");
        printf("4. Reset (Admin Only)\n");
        printf("5. Open Admin Console (Admin Only)\n");
        printf("6. Upgrade to Admin\n");
        printf("0. Exit\n");
        printf("Enter a command: ");

        int command;
        scanf("%d", &command);

        if (command == 0) {
            printf("Exiting...\n");
            break;
        } else {
            user_command(command);
        }
    }

    return 0;
}
