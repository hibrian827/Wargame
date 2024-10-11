#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char username[32];

void get_flag() {
    // Open the file in read-only mode
    int file = open("flag.txt", O_RDONLY);

    // Check if the file was opened successfully
    if (file < 0) {
        perror("Could not open flag.txt");
        return;
    }

    char buffer[256];  // Buffer to hold the content
    ssize_t bytes_read;

    // Read and write the content of the file to standard output
    while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    // Close the file
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

	printf("[hint] The address of get_flag() : %p\n", &get_flag);

	greet_user();
	echo_input();

	printf("Goodbye!\n");
	return 0;
}
