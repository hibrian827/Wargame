#include <stdio.h>
#include <signal.h>

void busted()
{
  puts("\n\nYou BUSTED\n\n");
  exit(0);
}

unsigned int init()
{
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stderr, 0, 2, 0);
  signal(14, (__sighandler_t)busted);
  return alarm(0x3Cu);
}

int flag()
{
  char s[104]; // [rsp+0h] [rbp-70h] BYREF
  FILE *stream; // [rsp+68h] [rbp-8h]

  stream = fopen("./flag", "r");
  fgets(s, 100, stream);
  return puts(s);
}

int menu()
{
  puts("\n1. Open santa's notebook and look at it");
  puts("2. Add name to kind list");
  puts("3. Go back to wyv3rn");
  return printf(">> ");
}


int main(int argc, const char **argv, const char **envp)
{
  char *v3; // rsi
  char *v4; // rdi
  long v5; // rdx
  long v6; // rcx
  long v7; // r8
  long v8; // r9
  const char *v9; // rsi
  long v10; // rdx
  long v11; // rcx
  long v12; // r8
  long v13; // r9
  char s2[8]; // [rsp+0h] [rbp-E0h] BYREF
  long v15; // [rsp+8h] [rbp-D8h]
  char v16[8]; // [rsp+10h] [rbp-D0h] BYREF
  long v17; // [rsp+18h] [rbp-C8h]
  char dest[8]; // [rsp+20h] [rbp-C0h] BYREF
  long v19; // [rsp+28h] [rbp-B8h]
  char v20[132]; // [rsp+30h] [rbp-B0h] BYREF
  char src[8]; // [rsp+B4h] [rbp-2Ch] BYREF
  int v22; // [rsp+BCh] [rbp-24h] BYREF
  FILE *stream; // [rsp+C0h] [rbp-20h]
  void *ptr; // [rsp+C8h] [rbp-18h]
  int v25; // [rsp+D4h] [rbp-Ch]
  int v26; // [rsp+D8h] [rbp-8h]
  int i; // [rsp+DCh] [rbp-4h]

  init(argc, argv, envp);
  intro();
  i = 0;
  v25 = 0;
  v22 = 0;
  v26 = 0;
  *(long *)src = 0x6E7233767977;
  memset(v20, 0, 0x80);
  *(long *)dest = 0;
  v19 = 0;
  *(long *)v16 = 0;
  v17 = 0;
  *(long *)s2 = 0;
  v15 = 0;
  ptr = malloc(8);
  stream = fopen("/dev/urandom", "r");
  fread(ptr, 7, 1, stream);
  v3 = src;
  v4 = dest;
  strcpy(dest, src);
  while ( 1 )
  {
    menu(v4, v3, v5, v6, v7, v8);
    fflush(stdout);
    v3 = (char *)&v22;
    v4 = "%d";
    __isoc99_scanf("%d", &v22);
    if ( v22 == 3 )
      break;
    if ( v22 <= 3 )
    {
      if ( v22 == 1 )
      {
        puts("\n-Kind kid list-");
        for ( i = 0; i <= 5; ++i )
          puts(&v20[16 * i]);
        puts("\n-Naughty kid list-");
        for ( i = 0; i <= 7; ++i )
          putchar(dest[i]);
        puts("");
      }
      else if ( v22 == 2 )
      {
        printf("\nPassword : ");
        fflush(stdout);
        __isoc99_scanf("%8s", s2);
        v3 = s2;
        if ( !strncmp((const char *)ptr, s2, 7) )
        {
          printf("Name : ");
          fflush(stdout);
          v3 = v16;
          __isoc99_scanf("%8s", v16);
          if ( v26 > 7 )
          {
            v4 = "Kind list full";
            puts("Kind list full");
          }
          else
          {
            v3 = v16;
            v4 = &v20[16 * v26];
            strcpy(v4, v16);
            ++v26;
          }
        }
        else
        {
          printf(s2);
          v4 = " is Wrong password!";
          puts(" is Wrong password!");
        }
      }
    }
  }
  v25 = 0;
  v9 = "wyv3rn";
  if ( !strcmp(v20, "wyv3rn") )
  {
    for ( i = 0; i <= 5; ++i )
    {
      v9 = &src[i];
      if ( !strcmp(&dest[i], v9) )
      {
        puts("Wyv3rn : My name is still remain on the naughty kid list!");
        exit(0);
      }
    }
    puts("\nWyv3rn : You did it!");
    puts("Wyv3rn : Here is flag!");
    flag("Wyv3rn : Here is flag!", v9, v10, v11, v12, v13);
    exit(0);
  }
  puts("Wyv3rn : My name is not on the kind kid list!");
  exit(0);
}