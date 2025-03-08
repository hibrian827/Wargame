// gcc -o main main.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void initialize() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

void win() {
	system("/bin/sh");
}

int main() {
	initialize();

	char inp[80] = {0};
	char buf[1000] = {0};

	puts("Welcome to the Repeat Service!");
	puts("Please put your string and length.");

	while (1) {
		printf("Pattern: ");
		int len = read(STDIN_FILENO, inp, 80);
		if (len == 0)
			break;
		if (inp[len - 1] == '\n') {
			inp[len - 1] = 0;
			len--;
		}

		int target_len = 0;
		printf("Target length: ");
		scanf("%d", &target_len);

		if (target_len > 1000) {
			puts("Too long :(");
			break;
		}

		int count = 0;
		while (count < target_len) {
			memcpy(buf + count, inp, len);
			count += len;
		}

		printf("%s\n", buf);
	}
	return 0;
}