#include <stdio.h>
#include <string.h>

char sel[2];

long command_check(long a1, int a2)
{
  long result; // rax
  int j; // [rsp+18h] [rbp-18h]
  unsigned int i; // [rsp+1Ch] [rbp-14h]

  for ( i = 0; ; ++i )
  {
    result = i;
    if ( (int)i >= a2 )
      break;
    for ( j = 0; j < strlen("~!#$%^&*()_+|`\\<>?,./;:'\"{}[]\n"); ++j )
    {
      if ( *(char *)((int)i + a1) == asc_402008[j] )
      {
        *(char *)((int)i + a1) = 120;
        break;
      }
    }
  }
  return result;
}

long read_data(void *a1, int a2)
{
  unsigned int v3; // [rsp+1Ch] [rbp-4h]

  v3 = read(0, a1, a2);
  *((char *)a1 + (int)v3 - 1) = 0;
  return command_check(a1, v3);
}

int main(int argc, const char **argv, const char **envp)
{
  char v4[64]; // [rsp+0h] [rbp-B0h] BYREF
  char s[104]; // [rsp+40h] [rbp-70h] BYREF
  int v6; // [rsp+A8h] [rbp-8h]
  int i; // [rsp+ACh] [rbp-4h]

  init(argc, argv, envp);
  for ( i = 0; i <= 9; ++i )
  {
    printf("Enter option : ");
    read_data(v4, 60);
    v6 = snprintf(s, 30, "ls -%s ", v4);
    printf("Enter path : ");
    read_data(&s[v6], 70);
    system(s);
    puts("Again? y/n");
    read(0, &sel, 2);
    if ( sel == 110 )
      break;
  }
  return 0;
}