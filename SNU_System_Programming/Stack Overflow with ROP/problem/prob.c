#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char username[32];

// Please use these gadgets to set the arguments
extern void gadget1();
extern void gadget2();
extern void gadget3();

// Call this function with valid arguments
void get_flag(int arg1, int arg2, int arg3) {
    int file = open("flag.txt", O_RDONLY);

    if (file < 0) {
        perror("Could not open flag.txt");
        return;
    }

	if (arg1 == 0x1111 && arg2 == 0x2222 && arg3 == 0x3333) {
        char buffer[256];  // Buffer to hold the content
        ssize_t bytes_read;

        while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
	}
    close(file);
}

void greet_user() {
	printf("Welcome! Please enter your username: ");
	read(0, username, sizeof(username) - 1);  // Ensures null termination
	username[strcspn(username, "\n")] = '\0';
	printf("Hello, %s!\n", username);
}

void echo_input() {
	char buffer[64];
	printf("What would you like me to repeat back? ");
	read(0, buffer, 128);  // Vulnerable read, allows overflow
	printf("You said: ");
	buffer[strcspn(buffer, "\n")] = '\0';
	puts(buffer);
}

int main() {
	setvbuf(stdin,0,2,0);
	setvbuf(stdout,0,2,0);

	greet_user();
	echo_input();

	printf("Goodbye!\n");
	return 0;
}
