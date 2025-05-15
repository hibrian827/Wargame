#include <stdio.h>

void sigsegv_handler(int a1)
{
  if ( a1 == 11 )
    exit(0);
}

void sigill_handler(int a1)
{
  if ( a1 == 4 )
    system("/bin/sh");
}

long run()
{
  int v1; // [rsp+Ch] [rbp-104h] BYREF
  char buf[256]; // [rsp+10h] [rbp-100h] BYREF

  setvbuf(stdout, 0, 2, 0);
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stderr, 0, 2, 0);
  signal(11, sigsegv_handler);
  signal(4, sigill_handler);
  printf("Enter size: ");
  __isoc99_scanf("%d", &v1);
  read(0, buf, v1);
  return 0;
}

int main(int argc, const char **argv, const char **envp)
{
  run();
  return 0;
}