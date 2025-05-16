#include <stdio.h>

int main(int argc, const char **argv, const char **envp)
{
  int i; // [rsp+8h] [rbp-28h]
  int v5; // [rsp+Ch] [rbp-24h]
  char buf[24]; // [rsp+10h] [rbp-20h] BYREF
  unsigned long v7; // [rsp+28h] [rbp-8h]

  v7 = __readfsqword(0x28);
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stderr, 0, 2, 0);
  do
  {
    printf("Input: ");
    v5 = read(0, buf, 0x100);
    for ( i = 1; i < v5; ++i )
      buf[i - 1] ^= buf[i];
    printf("You entered: %s\n", buf);
  }
  while ( strtok(buf, "exit") );
  return 0;
}