#include <stdio.h>
#include <string.h>

// check_table array based on the pseudocode
unsigned int check_table[6][12] = {
    {0x2,   0, 0, 0, 0, 0, 0, 0, 0,    0,    0,    0},
    {0x3,   0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x5,   0, 0, 0, 0, 0, 0, 0, 0xFD, 0xFF, 0xFF, 0xFF},
    {0x49,  0, 0, 0, 0, 0, 0, 0, 0xFC, 0xFF, 0xFF, 0xFF},
    {0xB,   0, 0, 0, 0, 0, 0, 0, 0x2,  0,    0,    0},
    {0x25,  0, 0, 0, 0, 0, 0, 0, 0x8,  0,    0,    0}
};

// Function to check if the key is valid
int check_key(int key, unsigned int table[6][12], unsigned int a3) {
    for (unsigned int i = 0; i < a3; ++i) {
        // printf("%d and %d = %d, %d\n", table[i][8] + key, table[i][0], (unsigned int)(table[i][8] + key) % table[i][0], table[i][4]);
        if ((unsigned int)(table[i][8] + key) % table[i][0] != table[i][4]) {
            return 0;
        }
    }
    return 1;
}

// Function to decode the encoded text
int decode_text(unsigned long long *encoded, unsigned int a2, unsigned int key, char *decoded) {
    for (unsigned int i = 0; i < a2; ++i) {
        printf("%d %hd\n", i, ((unsigned char*)encoded)[i]);
        decoded[i] = (key >> (8 * (i & 3))) ^ ((unsigned char*)encoded)[i];
    }
    decoded[a2] = '\0'; // Null-terminate the string
    return 0;
}

int main(int argc, const char **argv, const char **envp) {
    char v5[4];                   // Buffer for decoded text
    int v6;                       // Return value of main
    unsigned long long v7;        // Length of the decoded string
    const char *v8;               // Pointer to the decoded string
    unsigned long long v9;        // Another length variable
    char *v10;                    // Pointer to the buffer for decoded text
    unsigned int v11;             // Key input by user
    unsigned long long v12 = 29;  // Length of the encoded message
    int v13 = 0;                  // Status flag
    unsigned long long v14[3] = { // Encoded message
        0x7B480F5F5F5D134BLL,
        0x6E5168747451687ELL,
        0x6D3A337F5F7A232FLL
    };
    int v15[4];                   // Buffer for "lj>na"
    unsigned long long v16;       // Stack guard variable

    v13 = 0;
    memcpy(v15, "lj>na", 5);  // Copy "lj>na" into v15

    printf("**************************************\n");
    printf("**************************************\n");
    printf("**** WELCOME NEXT GEN CHALLENGERS ****\n");
    printf("**************************************\n");
    printf("**************************************\n\n");
    printf("Enter the key: ");
    scanf("%u", &v11);  // Get the key from the user

    if (v11 <= 0x989680) {
        if (check_key(v11, check_table, 6)) {
            v7 = v12 + 1;
            v10 = v5;
            v8 = v5;
            v9 = v7;
            decode_text(v14, v12, v11, v5);  // Decode the text
            printf("\n");
            printf("CONGRATULATIONS!\n");
            printf("Decoded: %s\n", v8);
        } else {
            printf("Wrong key!\n");
        }
        v13 = 0;
    } else {
        printf("Key is too big!\n");
        v13 = 0;
    }
}