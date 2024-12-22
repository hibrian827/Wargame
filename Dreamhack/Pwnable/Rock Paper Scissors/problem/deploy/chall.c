#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    char c, t[4] = "RPS";
    int i, p, r;
    srand(time(NULL));
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    for(i = 1; i <= 10; i++)
    {
        printf("Round %d of 10\n", i);
        printf("Put your hand out(R, P, S): ");
        scanf("%c", &c);
        while(getchar() != '\n');
        switch(c)
        {
            case 'R':
                p = 0;
                break;
            case 'P':
                p = 1;
                break;
            case 'S':
                p = 2;
                break;
            default:
                printf("Nope!\n");
                return 0;
        }
        sleep(1);
        r = rand() % 3;
        printf("You: %c Computer: %c\n", t[p], t[r]);
        if((r - p + 1) % 3)
        {
            printf("Nope!\n");
            return 0;
        }
    }
    int fd = open("./flag", O_RDONLY);
    char flag[64] = { 0, };
    read(fd, flag, 64);
    printf("Flag is %s\n", flag);
    close(fd);
    return 0;
}
