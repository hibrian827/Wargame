#include <stdio.h>

int sub_133F(int a1)
{
  int result; // rax
  char v2; // [rsp+Fh] [rbp-9h]
  int j; // [rsp+10h] [rbp-8h]
  int i; // [rsp+14h] [rbp-4h]

  for ( i = 0; i <= 3; ++i )
  {
    for ( j = 0; j <= 7; ++j )
    {
      v2 = *(_BYTE *)(a1 + 8LL * i + j);
      *(_BYTE *)(a1 + 8LL * i + j) = *(_BYTE *)(a1 + 8LL * (8 - i) - 8 + j);
      result = j;
      *(_BYTE *)(8LL * (8 - i) - 8 + a1 + j) = v2;
    }
  }
  return result;
}


int sub_158A(int a1, int a2, unsigned int a3)
{
  int result; // rax
  int j; // [rsp+20h] [rbp-8h]
  int i; // [rsp+24h] [rbp-4h]

  for ( i = 0; i <= 7; ++i )
  {
    for ( j = 0; j <= 7; ++j )
    {
      result = j;
      *(_BYTE *)(a1 + 8LL * i + j) ^= *(_BYTE *)((j + i) % a3 + a2);
    }
  }
  return result;
}


int sub_1407(int a1)
{
  int result; // rax
  char v2; // [rsp+Fh] [rbp-9h]
  int j; // [rsp+10h] [rbp-8h]
  int i; // [rsp+14h] [rbp-4h]

  for ( i = 0; i <= 7; ++i )
  {
    for ( j = 0; j <= 3; ++j )
    {
      v2 = *(_BYTE *)(a1 + 8LL * i + j);
      *(_BYTE *)(8LL * i + a1 + j) = *(_BYTE *)(a1 + 8LL * i + 7 - j);
      result = 7 - j;
      *(_BYTE *)(8LL * i + a1 + result) = v2;
    }
  }
  return result;
}


int sub_1622(int a1, int a2, unsigned int a3)
{
  int result; // rax
  int j; // [rsp+20h] [rbp-8h]
  int i; // [rsp+24h] [rbp-4h]

  for ( i = 0; i <= 7; ++i )
  {
    for ( j = 0; j <= 7; ++j )
    {
      result = j;
      *(_BYTE *)(a1 + 8LL * i + j) += *(_BYTE *)((j + i) % a3 + a2);
    }
  }
  return result;
}


int sub_14D0(int a1)
{
  int result; // rax
  char v2; // [rsp+Fh] [rbp-9h]
  int j; // [rsp+10h] [rbp-8h]
  int i; // [rsp+14h] [rbp-4h]

  for ( i = 0; i <= 7; ++i )
  {
    result = (unsigned int)i;
    for ( j = i; j <= 7; ++j )
    {
      v2 = *(_BYTE *)(a1 + 8LL * i + j);
      *(_BYTE *)(a1 + 8LL * i + j) = *(_BYTE *)(a1 + 8LL * j + i);
      result = i;
      *(_BYTE *)(8LL * j + a1 + i) = v2;
    }
  }
  return result;
}


int main()
{
  int j; // [rsp+8h] [rbp-58h]
  int i; // [rsp+Ch] [rbp-54h]
  char s[72]; // [rsp+10h] [rbp-50h] BYREF
  unsigned int v7; // [rsp+58h] [rbp-8h]

  v7 = __readfsqword(0x28u);
  setvbuf(stdout, 0LL, 2, 0LL);
  memset(s, 0, 0x40uLL);
  for ( i = 0; i <= 7; ++i )
  {
    for ( j = 0; j <= 7; ++j )
    {
      printf("value of (%d, %d)? ", (unsigned int)j, (unsigned int)i);
      scanf("%hhu", &s[8 * i + j]);
    }
  }
  sub_133F(s);
  sub_158A(s, &unk_2037, 8LL);
  sub_1407(s);
  sub_1622(s, &unk_2040, 8LL);
  sub_14D0(s);
  if ( !memcmp(s, &unk_2050, 0x40uLL) )
  {
    printf("correct :) flag is ");
    sub_1289();
    return 0LL;
  }
  else
  {
    puts("wrong :(");
    return 1LL;
  }
}