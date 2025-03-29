#include <stdio.h>
#include <string.h>

int sub_13A9()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  return setvbuf(stderr, 0LL, 2, 0LL);
}

int sub_140E()
{
  puts("Flag Printer v0.1");
  return puts("Please Enter Command(print,id,help):");
}

unsigned long sub_1437(char *a1)
{
  int v2; // eax
  unsigned int v4; // [rsp+18h] [rbp-38h]
  int i; // [rsp+1Ch] [rbp-34h]
  const char *s1; // [rsp+20h] [rbp-30h]
  char *v7; // [rsp+28h] [rbp-28h]
  char s2[5]; // [rsp+33h] [rbp-1Dh] BYREF
  unsigned long v9; // [rsp+38h] [rbp-18h]

  v9 = __readfsqword(0x28u);
  v4 = 0;
  a1[strcspn(a1, "\n")] = 0;
  s1 = strtok(a1, " ");
  while ( s1 )
  {
    if ( !strcmp(s1, "print") )
      return (unsigned long)v4 << 32;
    if ( !strcmp(s1, "id") )
      return ((unsigned long)v4 << 32) | 1;
    if ( !strcmp(s1, "help") )
      return ((unsigned long)v4 << 32) | 2;
    v7 = strdup(s1);
    for ( i = 0; v7[i]; ++i )
    {
      v2 = i;
      v7[v2] ^= 0x42u;
    }
    strcpy(s2, "&-17");
    if ( strcmp(v7, s2) )
    {
      free(v7);
      return ((unsigned long)v4 << 32) | 0xFFFFFFFF;
    }
    v4 = 1;
    s1 = strtok(0LL, " ");
    free(v7);
  }
  return ((unsigned long)v4 << 32) | 0xFFFFFFFF;
}

int sub_1749()
{
  puts("print: print out flag art");
  puts("id: print out your simple status");
  return puts("help: print out usable commands, just like this!");
}

int sub_1711(int a1)
{
  if ( a1 )
    return puts("id: user(godmode)");
  else
    return puts("id: user");
}

int sub_1673(int a1)
{
  const char *v1; // rax
  char i; // al
  FILE *stream; // [rsp+48h] [rbp-8h]

  if ( a1 )
    v1 = "./flag";
  else
    v1 = "./art";
  stream = fopen(v1, "r");
  for ( i = getc(stream); i != -1; i = getc(stream) )
    putchar(i);
  fclose(stream);
  return putchar(10);
}

void main(int a1, char **a2, char **a3)
{
  long v3; // rax
  char s[72]; // [rsp+10h] [rbp-50h] BYREF
  unsigned long v5; // [rsp+58h] [rbp-8h]

  v5 = __readfsqword(0x28u);
  sub_13A9(a1, a2, a3);
  sub_140E();
  while ( 1 )
  {
    while ( 1 )
    {
      printf("> ");
      fgets(s, 64, stdin);
      v3 = sub_1437(s);
      if ( (long)v3 != 2 )
        break;
      sub_1749();
    }
    if ( (int)v3 > 2 )
    {
LABEL_10:
      puts("Invalid Command!");
    }
    else if ( (long)v3 )
    {
      if ( (long)v3 != 1 )
        goto LABEL_10;
      sub_1711(HIDWORD(v3));
    }
    else
    {
      sub_1673(HIDWORD(v3));
    }
  }
}