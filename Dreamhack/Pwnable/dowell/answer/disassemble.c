#include <stdio.h>

int main(int argc, const char **argv, const char **envp)
{
  char *s[2]; // [rsp+0h] [rbp-10h] BYREF

  s[1] = (char *)__readfsqword(0x28u);
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  system('echo "I do well at getting the flag');
  printf("one chance for flag");
  putchar(10);
  printf("pt: ");
  __isoc99_scanf("%d", s);
  printf("input: ");
  __isoc99_scanf("%s", s[0]);
  printf("your input:");
  puts(s[0]);
  return 0;
}