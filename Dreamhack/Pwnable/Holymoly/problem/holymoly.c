/* holymoly.c
 * gcc -Wall -no-pie -s holymoly.c -o holymoly
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HOLYMOLY_ID         0
#define ROLYPOLY_ID         1
#define MONOPOLY_ID         2
#define GUACAMOLE_ID        3
#define ROBOCARPOLI_ID      4
#define HALLIGALLI_ID       5
#define BROCCOLI_ID         6
#define BORDERCOLLIE_ID     7
#define BLUEBERRY_ID        8
#define CRANBERRY_ID        9
#define MYSTERY_ID          10
#define INVALID_ID          11

#define HOLYMOLY        "holymoly"
#define ROLYPOLY        "rolypoly"
#define MONOPOLY        "monopoly"
#define GUACAMOLE       "guacamole"
#define ROBOCARPOLI     "robocarpoli"
#define HALLIGALLI      "halligalli"
#define BROCCOLI        "broccoli"
#define BORDERCOLLIE    "bordercollie"
#define BLUEBERRY       "blueberry"
#define CRANBERRY       "cranberry"
#define MYSTERY         "mystery"

#define SWITCH_VAL      0
#define SWITCH_PTR      1

struct phrase_t {
    uint8_t id;
    char *str;
    size_t len;
};

const struct phrase_t phrases[11] = {
    {.id = HOLYMOLY_ID,      .str = HOLYMOLY,     .len = sizeof(HOLYMOLY)},
    {.id = ROLYPOLY_ID,      .str = ROLYPOLY,     .len = sizeof(ROLYPOLY)},
    {.id = MONOPOLY_ID,      .str = MONOPOLY,     .len = sizeof(MONOPOLY)},
    {.id = GUACAMOLE_ID,     .str = GUACAMOLE,    .len = sizeof(GUACAMOLE)},
    {.id = ROBOCARPOLI_ID,   .str = ROBOCARPOLI,  .len = sizeof(ROBOCARPOLI)},
    {.id = HALLIGALLI_ID,    .str = HALLIGALLI,   .len = sizeof(HALLIGALLI)},
    {.id = BROCCOLI_ID,      .str = BROCCOLI,     .len = sizeof(BROCCOLI)},
    {.id = BORDERCOLLIE_ID,  .str = BORDERCOLLIE, .len = sizeof(BORDERCOLLIE)},
    {.id = BLUEBERRY_ID,     .str = BLUEBERRY,    .len = sizeof(BLUEBERRY)},
    {.id = CRANBERRY_ID,     .str = CRANBERRY,    .len = sizeof(CRANBERRY)},
    {.id = MYSTERY_ID,       .str = MYSTERY,      .len = sizeof(MYSTERY)},
};

int amounts[4] = {0x1000, 0x100, 0x10, 0x1};

uint64_t *ptr;
uint64_t val;
uint8_t ptrval_switch;

void Init();
void Interpret(char *song);
uint8_t Parse(char *song_ptr);
void ProcessPhraseID(uint8_t id);
void Increase(int amount);
void Decrease(int amount);
void Read();
void Write();
void OperateSwitch();

int main(void) {
    char *song;

    Init();
    printf("holymoly? ");
    song = calloc(0xbeef, 1);
    scanf("%48878s", song);
    Interpret(song);
    puts("holymoly!");
}

void Init() {
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);
    ptr = NULL;
    val = 0;
}

void Interpret(char *song) {
    uint8_t id;
    char *song_ptr;

    song_ptr = song;

    while (1) {
        id = Parse(song_ptr);
        if (id >= INVALID_ID)
            return;
        ProcessPhraseID(id);
        song_ptr += phrases[id].len - 1;
    }
}

uint8_t Parse(char *song_ptr) {
    int i;

    for (i = 0; i < sizeof(phrases) / sizeof(phrases[0]); i++)
        if (memcmp(phrases[i].str, song_ptr, phrases[i].len - 1) == 0)
            return phrases[i].id;

    return INVALID_ID;
}

void ProcessPhraseID(uint8_t id) {
    switch (id) {
    case HOLYMOLY_ID ... GUACAMOLE_ID:
        Increase(amounts[id - HOLYMOLY_ID]);
        break;
    case ROBOCARPOLI_ID ... BORDERCOLLIE_ID:
        Decrease(amounts[id - ROBOCARPOLI_ID]);
        break;
    case BLUEBERRY_ID:
        Read();
        break;
    case CRANBERRY_ID:
        Write();
        break;
    case MYSTERY_ID:
        OperateSwitch();
        break;
    }
}

void Increase(int amount) {
    if (ptrval_switch)
        ptr = (uint64_t *)((uint8_t *)ptr + amount);
    else
        val += amount;
}

void Decrease(int amount) {
    if (ptrval_switch)
        ptr = (uint64_t *)((uint8_t *)ptr - amount);
    else
        val -= amount;
}

void Read() {
    write(1, (char *)ptr, 8);
}

void Write() {
    *ptr = val;
}

void OperateSwitch() {
    ptrval_switch = ptrval_switch ? SWITCH_VAL : SWITCH_PTR;
}
