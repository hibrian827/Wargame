#include <stdio.h>

int sub_133F(unsigned char* a1)
{
    int result = 0; // Initialize result
    unsigned char v2; // Temporary variable for swapping
    int j, i; // Loop counters

    for (i = 0; i <= 3; ++i)
    {
        for (j = 0; j <= 7; ++j)
        {
            v2 = a1[8 * i + j];
            a1[8 * i + j] = a1[8 * (8 - i - 1) + j];
            result = j;
            a1[8 * (8 - i - 1) + j] = v2;
        }
    }
    return result;
}


int sub_158A(unsigned char* a1, unsigned char* a2, unsigned int a3)
{
    int result = 0; // Initialize result
    int j, i; // Loop counters

    for (i = 0; i <= 7; ++i)
    {
        for (j = 0; j <= 7; ++j)
        {
            result = j;
            a1[8 * i + j] ^= a2[(j + i) % a3];
        }
    }
    return result;
}


int sub_1407(unsigned char* a1)
{
    int result = 0; // Initialize result
    unsigned char v2; // Temporary variable for swapping
    int j, i; // Loop counters

    for (i = 0; i <= 7; ++i)
    {
        for (j = 0; j <= 3; ++j)
        {
            v2 = a1[8 * i + j];
            a1[8 * i + j] = a1[8 * i + 7 - j];
            result = 7 - j;
            a1[8 * i + result] = v2;
        }
    }
    return result;
}


int sub_1622(unsigned char* a1, unsigned char* a2, unsigned int a3)
{
    int result = 0; // Initialize result
    int j, i; // Loop counters

    for (i = 0; i <= 7; ++i)
    {
        for (j = 0; j <= 7; ++j)
        {
            result = j;
            a1[8 * i + j] += a2[(j + i) % a3];
        }
    }
    return result;
}


int sub_14D0(unsigned char* a1)
{
    int result = 0; // Initialize result
    unsigned char v2; // Temporary variable for swapping
    int j, i; // Loop counters

    for (i = 0; i <= 7; ++i)
    {
        result = i;
        for (j = i; j <= 7; ++j)
        {
            v2 = a1[8 * i + j];
            a1[8 * i + j] = a1[8 * j + i];
            result = i;
            a1[8 * j + i] = v2;
        }
    }
    return result;
}


int main()
{
  int j; // [rsp+8h] [rbp-58h]
  int i; // [rsp+Ch] [rbp-54h]
  unsigned char s[64] = {
    0x19, 0xdf, 0xf7, 0xfd, 0xc0, 0xae, 0x9b, 0xc8,
    0xe4, 0x5d, 0x06, 0xf5, 0x1d, 0x71, 0x0e, 0xee,
    0xc0, 0x1c, 0x3e, 0x14, 0x33, 0x32, 0x40, 0x69,
    0x35, 0x68, 0x02, 0xe2, 0xb7, 0x20, 0x1f, 0x3d,
    0xf5, 0x19, 0x57, 0xd2, 0x97, 0xdd, 0x30, 0x90,
    0x43, 0xbc, 0x7b, 0xa8, 0x15, 0x89, 0xbd, 0x53,
    0x40, 0xcf, 0x64, 0x3d, 0x8d, 0x03, 0xae, 0x2e,
    0x08, 0x5a, 0xae, 0x9a, 0x11, 0x9f, 0xb7, 0x65
  }; // [rsp+10h] [rbp-50h] BYREF
  unsigned int v7; // [rsp+58h] [rbp-8h]
  char num1[] = {0x15, 0x55, 0xc4, 0x3b, 0xb5, 0xfc, 0x35, 0xd7};
  char num2[] = {0xbf, 0xd6, 0x62, 0x87, 0x08, 0x62, 0xf2, 0x66};

  setvbuf(stdout, 0, 2, 0);
  
  // sub_133F(s);
  // sub_158A(s, num1, 8);
  // sub_1407(s);
  // sub_1622(s, num2, 8);
  // sub_14D0(s);
 for (int i = 0; i < 64; i++) {
    printf("array[%d] = 0x%02x\n", i, s[i]);
  }
}