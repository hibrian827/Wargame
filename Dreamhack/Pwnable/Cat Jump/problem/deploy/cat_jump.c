/* cat_jump.c
 * gcc -Wall -no-pie -fno-stack-protector cat_jump.c -o cat_jump
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CAT_JUMP_GOAL 37

#define CATNIP_PROBABILITY 0.1
#define CATNIP_INVINCIBLE_TIMES 3

#define OBSTACLE_PROBABILITY 0.5
#define OBSTACLE_LEFT  0
#define OBSTACLE_RIGHT 1

void Init() {
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);
}

void PrintBanner() {
    puts("                         .-.\n" \
         "                          \\ \\\n" \
         "                           \\ \\\n" \
         "                            | |\n" \
         "                            | |\n" \
         "          /\\---/\\   _,---._ | |\n" \
         "         /^   ^  \\,'       `. ;\n" \
         "        ( O   O   )           ;\n" \
         "         `.=o=__,'            \\\n" \
         "           /         _,--.__   \\\n" \
         "          /  _ )   ,'   `-. `-. \\\n" \
         "         / ,' /  ,'        \\ \\ \\ \\\n" \
         "        / /  / ,'          (,_)(,_)\n" \
         "       (,;  (,,)      jrei\n");
}

char cmd_fmt[] = "echo \"%s\" > /tmp/cat_db";

void StartGame() {
    char cat_name[32];
    char catnip;
    char cmd[64];
    char input;
    char obstacle;
    double p;
    unsigned char jump_cnt;

    srand(time(NULL));

    catnip = 0;
    jump_cnt = 0;

    puts("let the cat reach the roof! 🐈");

    sleep(1);

    do {
        // set obstacle with a specific probability.
        obstacle = rand() % 2;

        // get input.
        do {
            printf("left jump='h', right jump='j': ");
            scanf("%c%*c", &input);
        } while (input != 'h' && input != 'l');

        // jump.
        if (catnip) {
            catnip--;
            jump_cnt++;
            puts("the cat powered up and is invincible! nothing cannot stop! 🐈");
        } else if ((input == 'h' && obstacle != OBSTACLE_LEFT) ||
                (input == 'l' && obstacle != OBSTACLE_RIGHT)) {
            jump_cnt++;
            puts("the cat jumped successfully! 🐱");
        } else {
            puts("the cat got stuck by obstacle! 😿 🪨 ");
            return;
        }

        // eat some catnip with a specific probability.
        p = (double)rand() / RAND_MAX;
        if (p < CATNIP_PROBABILITY) {
            puts("the cat found and ate some catnip! 😽");
            catnip = CATNIP_INVINCIBLE_TIMES;
        }
    } while (jump_cnt < CAT_JUMP_GOAL);

    puts("your cat has reached the roof!\n");

    printf("let people know your cat's name 😼: ");
    scanf("%31s", cat_name);

    snprintf(cmd, sizeof(cmd), cmd_fmt, cat_name);
    system(cmd);

    printf("goodjob! ");
    system("cat /tmp/cat_db");
}

int main(void) {
    Init();
    PrintBanner();
    StartGame();

    return 0;
}
