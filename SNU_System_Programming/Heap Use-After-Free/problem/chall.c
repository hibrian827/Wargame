// gcc chall.c -o chall
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_MESSAGE_LEN 0x28
#define MAX_MESSAGE_NUM 10

#define ERRSTR_MESSAGE_DUP "Message already exists"
#define ERRSTR_MESSAGE_NOT_FOUND "Message does not exist"
#define ERRSTR_INDEX_NOT_FOUND "Invalid index"

typedef struct Message {
    char content[MAX_MESSAGE_LEN];
    int (*printer)(const char *);
} Message;

Message *Messages[MAX_MESSAGE_NUM] = {0, };
char *Feedback = NULL;
int Feedback_len = -1;

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int puts_red(const char *msg) {
    return printf("\033[1;31m%s\033[0m\n", msg);
}

int puts_green(const char *msg) {
    return printf("\033[1;32m%s\033[0m\n", msg);
}

void win(char *cmd) {
    system(cmd);
}

int read_msg_index() {
    int index;
    printf("Select message index (0 ~ %d): ", MAX_MESSAGE_NUM - 1);
    scanf("%d", &index);
    getchar();

    if (index < 0 || index >= MAX_MESSAGE_NUM) {
        return -1;
    }

    return index;
}

void process(int choice) {
    switch (choice) {
        case 1: {
            printf("=== Create message ===\n");
            int index;
            index = read_msg_index();
            if (index == -1) {
                puts(ERRSTR_INDEX_NOT_FOUND);
                break;
            }

            if (Messages[index]) {
                puts(ERRSTR_MESSAGE_DUP);
                break;
            }

            Message *msg = (Message *)malloc(sizeof(Message));
            printf("Input message: ");
            int nread = read(0, msg->content, MAX_MESSAGE_LEN);
            if (nread % 3 == 0) {
                msg->printer = &puts;
            } else if (nread % 3 == 1) {
                msg->printer = &puts_red;
            } else {
                msg->printer = &puts_green;
            }

            Messages[index] = msg;
            printf("Message created\n");
            break;
        }

        case 2: {
            printf("=== Delete message ===\n");
            int index;
            index = read_msg_index();
            if (index == -1) {
                puts(ERRSTR_INDEX_NOT_FOUND);
                break;
            }

            if (Messages[index] == NULL) {
                puts(ERRSTR_MESSAGE_NOT_FOUND);
                break;
            }

            free(Messages[index]);
            printf("Message deleted\n");
            break;
        }
        case 3: {
            printf("=== Show message ===\n");
            int index;
            index = read_msg_index();
            if (index == -1) {
                puts(ERRSTR_INDEX_NOT_FOUND);
                break;
            }

            if (Messages[index] == NULL) {
                puts(ERRSTR_MESSAGE_NOT_FOUND);
                break;
            }

            Message *msg = Messages[index];
            puts("===========================");
            msg->printer(msg->content);
            puts("===========================");
            Messages[index] = NULL;
            break;
        }
        case 4: {
            printf("=== Create feedback ===\n");
            if (Feedback != NULL) {
                puts("Sorry, you can only give feedback once");
                break;
            }

            int len;
            printf("How long is your feedback: ");
            scanf("%d", &len);
            getchar();

            if (len < 0 || len > 0x1000) {
                puts(ERRSTR_INDEX_NOT_FOUND);
                break;
            }

            Feedback = (char *)malloc(len);
            Feedback_len = len;
            printf("Give me your feedback: ");
            read(0, Feedback, len);

            printf("Thank you for your feedback\n");
            break;
        }
        case 5: {
            printf("=== Show feedback ===\n");
            if (Feedback == NULL) {
                printf("Feedback does not exist\n");
                break;
            }

            printf("[Begin of feedback]\n");
            write(1, Feedback, Feedback_len);
            printf("[End of feedback]\n");
            break;
        }
        case 6: {
            printf("=== Update feedback ===\n");
            if (Feedback == NULL) {
                printf("Feedback does not exist\n");
                break;
            }

            printf("Give me your new feedback: ");
            read(0, Feedback, Feedback_len);
            break;

        }
        case 7:
            printf("Exit\n");
            exit(1);
        default:
            printf("Invalid choice\n");
            break;
    }
}

int main() {
    init();

    while (1) {
        puts("");
        puts("=== Menu ===");
        puts("1. Create message");
        puts("2. Delete message");
        puts("3. Show message");
        puts("4. Create feedback");
        puts("5. Show feedback");
        puts("6. Update feedback");
        puts("7. Exit");

        int choice;
        printf("Your choice: ");
        scanf("%d", &choice);
        getchar();

        process(choice);
    }
}
